#Requires -Version 5.1
# Fase 4: runtime zoom — capture before/after numpad +/- (no GEN_UI_SCALE; start at 1.0).
# Usage: .\capture_p4_zoom.ps1

Add-Type -AssemblyName System.Drawing

$outDir = "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\captures\uiscale"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$code = @"
using System;
using System.Runtime.InteropServices;
public class Win32UiscaleP4 {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
  public const uint KEYEVENTF_KEYUP = 0x0002;
  public const byte VK_ADD = 0x6B;
  public const byte VK_SUBTRACT = 0x6D;
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
  $r = New-Object Win32UiscaleP4+RECT
  [Win32UiscaleP4]::GetWindowRect($hwnd, [ref]$r) | Out-Null
  $w = $r.Right - $r.Left
  $h = $r.Bottom - $r.Top
  if ($w -le 0 -or $h -le 0) { throw "bad window size ${w}x${h}" }

  $ok = $false
  for ($attempt = 1; $attempt -le 4; $attempt++) {
    [Win32UiscaleP4]::SetForegroundWindow($hwnd) | Out-Null
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

function Send-Vk([byte]$vk) {
  [Win32UiscaleP4]::keybd_event($vk, 0, 0, [UIntPtr]::Zero)
  Start-Sleep -Milliseconds 50
  [Win32UiscaleP4]::keybd_event($vk, 0, [Win32UiscaleP4]::KEYEVENTF_KEYUP, [UIntPtr]::Zero)
}

$exe = "E:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\CMake\Build\Windows\intel64\ui_system.exe"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Milliseconds 500

# Ensure a clean start at scale 1.0 (ini may have been written by a prior zoom session).
Remove-Item Env:GEN_UI_SCALE -ErrorAction SilentlyContinue
$iniCandidates = @(
  (Join-Path (Split-Path $exe) "ui_system.ini"),
  "e:\Projects\GEN_FrameWork\Examples\Graphics\UI_System\assets\ui_system.ini"
)
foreach ($ini in $iniCandidates) {
  if (Test-Path $ini) {
    $txt = Get-Content $ini -Raw
    if ($txt -match '(?m)^uiscale=') {
      $txt = $txt -replace '(?m)^uiscale=.*$', 'uiscale=1.0'
    } else {
      $txt = $txt -replace '(?m)^(\[general\])', "`$1`r`nuiscale=1.0"
    }
    Set-Content -Path $ini -Value $txt -NoNewline
    Write-Host "reset uiscale=1.0 in $ini"
  }
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

Capture-Window $hwnd (Join-Path $outDir "P4_before_scale1.png")

[Win32UiscaleP4]::SetForegroundWindow($hwnd) | Out-Null
Start-Sleep -Milliseconds 200
# Two + steps → 1.5
Send-Vk ([Win32UiscaleP4]::VK_ADD)
Start-Sleep -Seconds 1
Send-Vk ([Win32UiscaleP4]::VK_ADD)
Start-Sleep -Seconds 2
if ($p.HasExited) { throw "ui_system exited after zoom-in" }

Capture-Window $hwnd (Join-Path $outDir "P4_after_scale15.png")

# One - step → 1.25
Send-Vk ([Win32UiscaleP4]::VK_SUBTRACT)
Start-Sleep -Seconds 2
Capture-Window $hwnd (Join-Path $outDir "P4_after_scale125.png")

@"
# Fase 4 — Runtime zoom checklist

Fecha: $(Get-Date -Format 'yyyy-MM-dd')
Keys: numpad ``+`` / ``-`` (step 0.25). Persist: ``[general] uiscale`` in ui_system.ini.

| Captura | Scale esperado |
|---------|----------------|
| ``P4_before_scale1.png`` | 1.0 |
| ``P4_after_scale15.png`` | 1.5 (two ``+``) |
| ``P4_after_scale125.png`` | 1.25 (one ``-``) |

"@ | Set-Content (Join-Path $outDir "P4_zoom_checklist.md")

Write-Host "P4 captures done"
Get-Process ui_system -ErrorAction SilentlyContinue | Stop-Process -Force
