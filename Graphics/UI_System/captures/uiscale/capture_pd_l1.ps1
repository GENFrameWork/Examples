#Requires -Version 5.1
# Track D+L1 validation: launch UI_System, capture Resumen + CPU (grid + CSS font-size).
Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$code = @"
using System;
using System.Runtime.InteropServices;
public class Win32UiscalePD {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int X, int Y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
  [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hWnd, ref POINT lpPoint);
  public static readonly IntPtr HWND_TOPMOST = new IntPtr(-1);
  public static readonly IntPtr HWND_NOTOPMOST = new IntPtr(-2);
  public const uint SWP_NOMOVE = 0x0002;
  public const uint SWP_NOSIZE = 0x0001;
  public const uint SWP_SHOWWINDOW = 0x0040;
  public const uint MOUSEEVENTF_LEFTDOWN = 0x0002;
  public const uint MOUSEEVENTF_LEFTUP   = 0x0004;
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@
Add-Type -TypeDefinition $code

function Test-CaptureOk([System.Drawing.Bitmap]$bmp) {
  $sample = @(@(200,200), @(720,450), @(1000,400), @(400,300), @(80,120))
  $lit = 0
  foreach ($p in $sample) {
    if ($p[0] -ge $bmp.Width -or $p[1] -ge $bmp.Height) { continue }
    $c = $bmp.GetPixel($p[0], $p[1])
    if (($c.R + $c.G + $c.B) -gt 30) { $lit++ }
  }
  return ($lit -ge 2)
}

function Capture-Window([IntPtr]$hwnd, [string]$path) {
  $r = New-Object Win32UiscalePD+RECT
  [Win32UiscalePD]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }

  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscalePD]::SetForegroundWindow($hwnd) | Out-Null
    Start-Sleep -Milliseconds 250
    $bmp = New-Object System.Drawing.Bitmap $w, $h
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($r.Left, $r.Top, 0, 0, (New-Object System.Drawing.Size($w, $h)))
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
  $pt = New-Object Win32UiscalePD+POINT
  $pt.X = $cx; $pt.Y = $cy
  [Win32UiscalePD]::ClientToScreen($hwnd, [ref]$pt) | Out-Null
  [Win32UiscalePD]::SetCursorPos($pt.X, $pt.Y) | Out-Null
  Start-Sleep -Milliseconds 80
  [Win32UiscalePD]::mouse_event([Win32UiscalePD]::MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 40
  [Win32UiscalePD]::mouse_event([Win32UiscalePD]::MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
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
[Win32UiscalePD]::ShowWindow($hwnd, 9) | Out-Null
[Win32UiscalePD]::SetWindowPos($hwnd, [Win32UiscalePD]::HWND_TOPMOST, 0, 0, 0, 0, [Win32UiscalePD]::SWP_NOMOVE -bor [Win32UiscalePD]::SWP_NOSIZE -bor [Win32UiscalePD]::SWP_SHOWWINDOW) | Out-Null
[Win32UiscalePD]::SetForegroundWindow($hwnd) | Out-Null
Start-Sleep -Seconds 1

Capture-Window $hwnd (Join-Path $outDir "PD_L1_resumen_grid.png")

# CPU section (chart overlay + same top grid)
Click-Client $hwnd 105 150
Start-Sleep -Seconds 2
Capture-Window $hwnd (Join-Path $outDir "PD_L1_cpu_grid.png")

[Win32UiscalePD]::SetWindowPos($hwnd, [Win32UiscalePD]::HWND_NOTOPMOST, 0, 0, 0, 0, [Win32UiscalePD]::SWP_NOMOVE -bor [Win32UiscalePD]::SWP_NOSIZE) | Out-Null

@"
# Track D + L.1 validation

- D.2: card-title / nav-label / foot use CSS ``font-size`` (no XML sizefont on those nodes)
- D.3: paint policy in GEN_UI_CSS_Lite_Roadmap.md (form borders; radial halo)
- L.1: ``form.cards-grid`` wraps top three cards (376 + 22 gap)
- Captures: PD_L1_resumen_grid.png, PD_L1_cpu_grid.png
- Gate: Nivel 1 (B/P deferred)
"@ | Set-Content -Encoding UTF8 (Join-Path $outDir "PD_L1_notes.md")

Write-Host "PD/L1 capture done."
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
