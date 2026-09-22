#Requires -Version 5.1
# Fase 6: min hit-target — scale 0.75 + click just outside paint AABB (inside expanded hit).
# Usage: .\capture_p6_minhit.ps1

Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$Scale = 0.75
$Prefix = "P6_scale075"

$code = @"
using System;
using System.Runtime.InteropServices;
public class Win32UiscaleP6 {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr hWnd, IntPtr hdcBlt, int nFlags);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int X, int Y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
  public const uint MOUSEEVENTF_LEFTDOWN = 0x0002;
  public const uint MOUSEEVENTF_LEFTUP   = 0x0004;
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
}
"@
Add-Type -TypeDefinition $code

function Test-CaptureOk([System.Drawing.Bitmap]$bmp) {
  $sample = @(@(200,200), @(720,450), @(1000,400), @(400,300), @(900,500))
  $lit = 0
  foreach ($p in $sample) {
    if ($p[0] -ge $bmp.Width -or $p[1] -ge $bmp.Height) { continue }
    $c = $bmp.GetPixel($p[0], $p[1])
    if (($c.R + $c.G + $c.B) -gt 30) { $lit++ }
  }
  return ($lit -ge 2)
}

function Capture-Window([IntPtr]$hwnd, [string]$path) {
  $r = New-Object Win32UiscaleP6+RECT
  [Win32UiscaleP6]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }

  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscaleP6]::SetForegroundWindow($hwnd) | Out-Null
    Start-Sleep -Milliseconds 250
    $bmp = New-Object System.Drawing.Bitmap $w, $h
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    if ($attempt -le 2) {
      $g.CopyFromScreen($r.Left, $r.Top, 0, 0, (New-Object System.Drawing.Size($w, $h)))
    } else {
      $hdc = $g.GetHdc()
      [Win32UiscaleP6]::PrintWindow($hwnd, $hdc, 2) | Out-Null
      $g.ReleaseHdc($hdc)
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
  $wr = New-Object Win32UiscaleP6+RECT
  [Win32UiscaleP6]::GetWindowRect($hwnd, [ref]$wr) | Out-Null
  $sx = $wr.Left + $cx
  $sy = $wr.Top + $cy
  [Win32UiscaleP6]::SetForegroundWindow($hwnd) | Out-Null
  [Win32UiscaleP6]::SetCursorPos($sx, $sy) | Out-Null
  Start-Sleep -Milliseconds 80
  [Win32UiscaleP6]::mouse_event([Win32UiscaleP6]::MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 40
  [Win32UiscaleP6]::mouse_event([Win32UiscaleP6]::MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
  Write-Host "click client ($cx,$cy) -> screen ($sx,$sy)"
}

function Get-AppWindow {
  for ($i = 0; $i -lt 20; $i++) {
    $proc = Get-Process ui_system -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne [IntPtr]::Zero } | Select-Object -First 1
    if ($proc) { return $proc.MainWindowHandle }
    Start-Sleep -Milliseconds 200
  }
  return [IntPtr]::Zero
}

function Get-ScreenClick([double]$dx, [double]$dy, [double]$scale, [int]$sw = 1440, [int]$sh = 900) {
  $pw = 1440.0 * $scale
  $ph = 900.0 * $scale
  $ox = 0.0; $oy = 0.0
  if ($pw -le $sw -and $ph -le $sh) {
    $ox = ($sw - $pw) * 0.5
    $oy = ($sh - $ph) * 0.5
  }
  return @{
    X = [int][Math]::Round($dx * $scale + $ox)
    Y = [int][Math]::Round($dy * $scale + $oy)
  }
}

$exe = "E:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\CMake\Build\Windows\intel64\ui_system.exe"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Milliseconds 600

$env:GEN_UI_SCALE = "$Scale"
Write-Host "GEN_UI_SCALE=$env:GEN_UI_SCALE (Fase 6 min-hit)"
Start-Process $exe
Start-Sleep -Seconds 8

$p = $null
for ($i = 0; $i -lt 60; $i++) {
  $p = Get-Process ui_system -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne [IntPtr]::Zero } | Select-Object -First 1
  if ($p) { break }
  Start-Sleep -Milliseconds 500
}
if (-not $p) { throw "ui_system has no window" }

$hwnd = $p.MainWindowHandle
[Win32UiscaleP6]::ShowWindow($hwnd, 9) | Out-Null
[Win32UiscaleP6]::SetForegroundWindow($hwnd) | Out-Null
Start-Sleep -Milliseconds 800

# Nav Disco
$dis = Get-ScreenClick 105 318 $Scale
$hwnd = Get-AppWindow
Click-Client $hwnd $dis.X $dis.Y
Start-Sleep -Seconds 3
$hwnd = Get-AppWindow
Capture-Window $hwnd (Join-Path $outDir "${Prefix}_disco.png")

# Margin hit: design (661,786) — 1px left of paint left=662, inside expanded hit left=660
$margin = Get-ScreenClick 661 786 $Scale
$hwnd = Get-AppWindow
Click-Client $hwnd $margin.X $margin.Y
Start-Sleep -Seconds 2
$hwnd = Get-AppWindow
Capture-Window $hwnd (Join-Path $outDir "${Prefix}_disk_margin_hit.png")

# Center next (sanity)
$next = Get-ScreenClick 966 786 $Scale
$hwnd = Get-AppWindow
Click-Client $hwnd $next.X $next.Y
Start-Sleep -Seconds 2

@"
# Fase 6 — Min hit checklist (auto)

- Fecha: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')
- GEN_UI_SCALE: $Scale
- minHitSize: 44 design px
- Margin click design: (661, 786) outside paint 40x40, inside hit 44x44
- Capturas: ${Prefix}_disco.png, ${Prefix}_disk_margin_hit.png
"@ | Set-Content -Path (Join-Path $outDir "P6_minhit_run.md") -Encoding UTF8

Write-Host "P6 captures done"
Get-ChildItem $outDir -Filter "${Prefix}_*.png" | Select-Object Name, Length

Remove-Item Env:GEN_UI_SCALE -ErrorAction SilentlyContinue
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
