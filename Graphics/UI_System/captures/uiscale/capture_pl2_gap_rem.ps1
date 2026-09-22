#Requires -Version 5.1
# Track L.2: rem gaps — launch UI_System, capture Resumen (sidebar row-gap 0.5rem + cards-grid 1.375rem).
Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$code = @"
using System;
using System.Runtime.InteropServices;
public class Win32UiscalePL2 {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);
  public static readonly IntPtr HWND_TOPMOST = new IntPtr(-1);
  public static readonly IntPtr HWND_NOTOPMOST = new IntPtr(-2);
  public const uint SWP_NOMOVE = 0x0002;
  public const uint SWP_NOSIZE = 0x0001;
  public const uint SWP_SHOWWINDOW = 0x0040;
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
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
  $r = New-Object Win32UiscalePL2+RECT
  [Win32UiscalePL2]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }
  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscalePL2]::SetForegroundWindow($hwnd) | Out-Null
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
  if (-not $ok) { throw "capture failed: $path" }
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
[Win32UiscalePL2]::ShowWindow($hwnd, 9) | Out-Null
[Win32UiscalePL2]::SetWindowPos($hwnd, [Win32UiscalePL2]::HWND_TOPMOST, 0, 0, 0, 0, [Win32UiscalePL2]::SWP_NOMOVE -bor [Win32UiscalePL2]::SWP_NOSIZE -bor [Win32UiscalePL2]::SWP_SHOWWINDOW) | Out-Null
Start-Sleep -Seconds 1
Capture-Window $hwnd (Join-Path $outDir "PL2_gap_rem.png")
[Win32UiscalePL2]::SetWindowPos($hwnd, [Win32UiscalePL2]::HWND_NOTOPMOST, 0, 0, 0, 0, [Win32UiscalePL2]::SWP_NOMOVE -bor [Win32UiscalePL2]::SWP_NOSIZE) | Out-Null

@"
# Track L.2 rem gaps

- ``form.sidebar-nav { row-gap: 0.5rem; }`` (= 8px at root 16)
- ``form.cards-grid { column-gap: 1.375rem; }`` (= 22px)
- flex-basis also resolves rem/vw/vh when stylesheet present
- Capture: PL2_gap_rem.png — layout should match PD_L1 (same pixel gaps)
"@ | Set-Content -Encoding UTF8 (Join-Path $outDir "PL2_gap_rem_notes.md")

Write-Host "PL2 capture done."
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
