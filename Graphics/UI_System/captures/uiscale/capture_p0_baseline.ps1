#Requires -Version 5.1
# Fase 0 baseline: launch UI_System, capture Resumen/CPU/Memoria/Disco via PrintWindow + nav clicks.
Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$code = @'
using System;
using System.Runtime.InteropServices;
public class Win32UiscaleP0 {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hWnd, ref POINT lpPoint);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr hWnd, IntPtr hdcBlt, int nFlags);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int X, int Y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
  public const uint MOUSEEVENTF_LEFTDOWN = 0x0002;
  public const uint MOUSEEVENTF_LEFTUP   = 0x0004;
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
'@
Add-Type -TypeDefinition $code

function Test-CaptureOk([System.Drawing.Bitmap]$bmp) {
  # Reject near-black / empty frames (PrintWindow race with GL present).
  $sample = @(@(40,40), @(720,450), @(1400,860), @(200,200), @(1000,300))
  $lit = 0
  foreach ($p in $sample) {
    $c = $bmp.GetPixel($p[0], $p[1])
    if (($c.R + $c.G + $c.B) -gt 30) { $lit++ }
  }
  return ($lit -ge 2)
}

function Capture-Window([IntPtr]$hwnd, [string]$path) {
  $r = New-Object Win32UiscaleP0+RECT
  [Win32UiscaleP0]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }

  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscaleP0]::SetForegroundWindow($hwnd) | Out-Null
    Start-Sleep -Milliseconds 250
    $bmp = New-Object System.Drawing.Bitmap $w, $h
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    if ($attempt -le 2) {
      $hdc = $g.GetHdc()
      [Win32UiscaleP0]::PrintWindow($hwnd, $hdc, 2) | Out-Null
      $g.ReleaseHdc($hdc)
    } else {
      $g.CopyFromScreen($r.Left, $r.Top, 0, 0, (New-Object System.Drawing.Size($w, $h)))
    }
    if (Test-CaptureOk $bmp) {
      $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
      $ok = $true
      Write-Host "saved $path (${w}x${h}) attempt=$attempt"
      $g.Dispose(); $bmp.Dispose()
      break
    }
    $g.Dispose(); $bmp.Dispose()
    Start-Sleep -Milliseconds 400
  }
  if (-not $ok) { throw "capture failed (black frame): $path" }
}

function Click-Client([IntPtr]$hwnd, [int]$cx, [int]$cy) {
  $pt = New-Object Win32UiscaleP0+POINT
  $pt.X = $cx; $pt.Y = $cy
  [Win32UiscaleP0]::ClientToScreen($hwnd, [ref]$pt) | Out-Null
  [Win32UiscaleP0]::SetCursorPos($pt.X, $pt.Y) | Out-Null
  Start-Sleep -Milliseconds 80
  [Win32UiscaleP0]::mouse_event([Win32UiscaleP0]::MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 40
  [Win32UiscaleP0]::mouse_event([Win32UiscaleP0]::MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
  Write-Host "click client ($cx,$cy) -> screen ($($pt.X),$($pt.Y))"
}

$exe = "E:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\CMake\Build\Windows\intel64\ui_system.exe"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Milliseconds 600
Start-Process $exe
Start-Sleep -Seconds 5

$p = $null
for ($i = 0; $i -lt 30; $i++) {
  $p = Get-Process ui_system -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne [IntPtr]::Zero } | Select-Object -First 1
  if ($p) { break }
  Start-Sleep -Milliseconds 250
}
if (-not $p) { throw "ui_system has no window" }

$hwnd = $p.MainWindowHandle
[Win32UiscaleP0]::ShowWindow($hwnd, 9) | Out-Null
[Win32UiscaleP0]::SetForegroundWindow($hwnd) | Out-Null
Start-Sleep -Milliseconds 600

$wr = New-Object Win32UiscaleP0+RECT
$cr = New-Object Win32UiscaleP0+RECT
[Win32UiscaleP0]::GetWindowRect($hwnd, [ref]$wr) | Out-Null
[Win32UiscaleP0]::GetClientRect($hwnd, [ref]$cr) | Out-Null
$ww = $wr.Right - $wr.Left; $wh = $wr.Bottom - $wr.Top
$cw = $cr.Right - $cr.Left; $ch = $cr.Bottom - $cr.Top
@"
# Fase 0 — medidas de ventana (runtime)

- Fecha: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')
- Exe: ``$exe``
- HWND: $hwnd
- GetWindowRect: ${ww}x${wh} (incluye chrome)
- GetClientRect: ${cw}x${ch} (superficie cliente)
- Design canvas (codigo Ini_Graphics): **1440 x 900**
- Client vs design: $(if ($cw -eq 1440 -and $ch -eq 900) { 'coincide' } else { "cliente=${cw}x${ch} vs design=1440x900" })
"@ | Set-Content -Path (Join-Path $outDir "P0_window_metrics.md") -Encoding UTF8
Write-Host "window=${ww}x${wh} client=${cw}x${ch}"

# Default section = Resumen
Start-Sleep -Seconds 1
Capture-Window $hwnd (Join-Path $outDir "P0_resumen.png")

# Sidebar nav-hit buttons (absolute, bottom-anchored ypos in XML):
# resumen ypos=118 h=48 -> top=70  cy=94
# cpu     ypos=174       -> top=126 cy=150
# memoria ypos=230       -> top=182 cy=206
# red     ypos=286       -> top=238 cy=262
# disco   ypos=342       -> top=294 cy=318
$navX = 105
$map = @(
  @{ Name = "cpu";     Y = 150 },
  @{ Name = "memoria"; Y = 206 },
  @{ Name = "disco";   Y = 318 }
)

foreach ($item in $map) {
  [Win32UiscaleP0]::SetForegroundWindow($hwnd) | Out-Null
  Start-Sleep -Milliseconds 200
  Click-Client $hwnd $navX $item.Y
  Start-Sleep -Seconds 2
  Capture-Window $hwnd (Join-Path $outDir ("P0_{0}.png" -f $item.Name))
}

# Disk pager hit buttons (bottom-anchored ypos):
# disk_prev xpos=662 ypos=806 h=40 -> top=766 cy=786 cx=682
# disk_next xpos=946 ypos=806 h=40 -> top=766 cy=786 cx=966
# Stay on Disco section; click next then prev to exercise card hit-tests.
Click-Client $hwnd 966 786
Start-Sleep -Seconds 1
Capture-Window $hwnd (Join-Path $outDir "P0_disco_page2.png")
Click-Client $hwnd 682 786
Start-Sleep -Seconds 1
Capture-Window $hwnd (Join-Path $outDir "P0_disco_page1.png")

Write-Host "P0 captures done"
Get-ChildItem $outDir -Filter "P0_*.png" | Select-Object Name, Length