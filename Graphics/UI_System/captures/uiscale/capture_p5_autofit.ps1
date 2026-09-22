#Requires -Version 5.1
# Fase 5: autofit — capture at small vs design-size window (scale = min(sw/dw, sh/dh)).
# Usage: .\capture_p5_autofit.ps1

Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$code = @"
using System;
using System.Runtime.InteropServices;
public class Win32UiscaleP5 {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);
  public const uint SWP_NOMOVE = 0x0002;
  public const uint SWP_NOZORDER = 0x0004;
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
}
"@
Add-Type -TypeDefinition $code

function Test-CaptureOk([System.Drawing.Bitmap]$bmp) {
  $sample = @(@(80,80), @(200,200), @(400,300), @(500,350))
  $lit = 0
  foreach ($p in $sample) {
    if ($p[0] -ge $bmp.Width -or $p[1] -ge $bmp.Height) { continue }
    $c = $bmp.GetPixel($p[0], $p[1])
    if (($c.R + $c.G + $c.B) -gt 30) { $lit++ }
  }
  return ($lit -ge 2)
}

function Capture-Window([IntPtr]$hwnd, [string]$path) {
  $r = New-Object Win32UiscaleP5+RECT
  [Win32UiscaleP5]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }

  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscaleP5]::SetForegroundWindow($hwnd) | Out-Null
    Start-Sleep -Milliseconds 300
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

function Resize-Client([IntPtr]$hwnd, [int]$cw, [int]$ch) {
  # Borderless UI_System: client == window outer size.
  [Win32UiscaleP5]::SetWindowPos($hwnd, [IntPtr]::Zero, 0, 0, $cw, $ch,
    [Win32UiscaleP5]::SWP_NOMOVE -bor [Win32UiscaleP5]::SWP_NOZORDER) | Out-Null
  Start-Sleep -Seconds 2
  $cr = New-Object Win32UiscaleP5+RECT
  [Win32UiscaleP5]::GetClientRect($hwnd, [ref]$cr) | Out-Null
  Write-Host "resized client $(($cr.Right-$cr.Left))x$(($cr.Bottom-$cr.Top)) (requested ${cw}x${ch})"
}

$exe = "E:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\CMake\Build\Windows\intel64\ui_system.exe"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Milliseconds 500

Remove-Item Env:GEN_UI_SCALE -ErrorAction SilentlyContinue
$ini = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\assets\ui_system.ini"
if (Test-Path $ini) {
  $txt = Get-Content $ini -Raw
  if ($txt -match '(?m)^uiscale=') { $txt = $txt -replace '(?m)^uiscale=.*$', 'uiscale=1.0' }
  else { $txt = $txt -replace '(?m)^(\[general\])', "`$1`r`nuiscale=1.0" }
  if ($txt -match '(?m)^uiscale_autofit=') { $txt = $txt -replace '(?m)^uiscale_autofit=.*$', 'uiscale_autofit=si' }
  else { $txt = $txt -replace '(?m)^(\[general\])', "`$1`r`nuiscale_autofit=si" }
  Set-Content -Path $ini -Value $txt -NoNewline
  Write-Host "ini: uiscale=1.0 autofit=si"
}

Start-Process $exe -WorkingDirectory (Split-Path $exe)
$p = $null
for ($i = 0; $i -lt 60; $i++) {
  $p = Get-Process ui_system -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne [IntPtr]::Zero } | Select-Object -First 1
  if ($p) { break }
  Start-Sleep -Milliseconds 500
}
if (-not $p) { throw "ui_system has no window" }
$hwnd = $p.MainWindowHandle
Start-Sleep -Seconds 3

# Design size (fit ≈ 1.0)
Resize-Client $hwnd 1440 900
Capture-Window $hwnd (Join-Path $outDir "P5_fit_1440x900.png")

# Half size (fit ≈ 0.5)
Resize-Client $hwnd 720 450
if ($p.HasExited) { throw "ui_system exited after resize to 720x450" }
Capture-Window $hwnd (Join-Path $outDir "P5_fit_720x450.png")

# Wider than design, same height (fit ≈ 1.0, pillarbox)
Resize-Client $hwnd 1600 900
if ($p.HasExited) { throw "ui_system exited after resize to 1600x900" }
Capture-Window $hwnd (Join-Path $outDir "P5_fit_1600x900.png")

@"
# Fase 5 — Autofit checklist

Fecha: $(Get-Date -Format 'yyyy-MM-dd')
Design: 1440×900 · scale = min(sw/dw, sh/dh) · ``uiscale_autofit=si``

| Captura | Ventana | Scale esperado |
|---------|---------|----------------|
| ``P5_fit_1440x900.png`` | 1440×900 | ≈ 1.0 |
| ``P5_fit_720x450.png`` | 720×450 | ≈ 0.5 |
| ``P5_fit_1600x900.png`` | 1600×900 | ≈ 1.0 (+ pillarbox) |

UI_Options: sin stylesheet → sin autofit (legacy). Android: diferido este ciclo.

"@ | Set-Content (Join-Path $outDir "P5_autofit_checklist.md")

Write-Host "P5 captures done"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
