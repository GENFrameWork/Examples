#Requires -Version 5.1
<#
.SYNOPSIS
  Cambia el ejemplo activo de CMake Tools en Cursor/VS Code.
.PARAMETER ExampleRelPath
  Ruta relativa bajo Examples, p.ej. Console/MiniWebServer
#>
param(
  [Parameter(Mandatory = $true)]
  [string]$ExampleRelPath
)

$ErrorActionPreference = 'Stop'

$examplesRoot = Split-Path -Parent $PSScriptRoot   # .../Examples
$repoRoot     = Split-Path -Parent $examplesRoot   # .../GEN_FrameWork
$cmakeDir     = Join-Path $examplesRoot ($ExampleRelPath -replace '/', '\') | Join-Path -ChildPath 'CMake'

if (-not (Test-Path (Join-Path $cmakeDir 'CMakeLists.txt'))) {
  Write-Error "No existe CMakeLists.txt en: $cmakeDir"
}

$posixRel = ($ExampleRelPath -replace '\\', '/').Trim('/')
$wsRel    = "`${workspaceFolder:Examples}/$posixRel/CMake"
$exRel    = "`${workspaceFolder}/$posixRel/CMake"
$compile  = "$wsRel/compile_commands.json"
$compileEx = "$exRel/compile_commands.json"

function Set-JsonStringProp([string]$json, [string]$prop, [string]$value) {
  $escaped = $value.Replace('\', '\\').Replace('"', '\"')
  $pattern = '"' + [regex]::Escape($prop) + '"\s*:\s*"[^"]*"'
  $replacement = '"' + $prop + '": "' + $escaped + '"'
  if ($json -notmatch $pattern) {
    throw "No se encontro la propiedad '$prop' en el JSON."
  }
  return [regex]::Replace($json, $pattern, $replacement, 1)
}

# 1) Workspace multi-root
$workspaceFile = Join-Path $repoRoot 'GEN_FrameWork.code-workspace'
if (Test-Path $workspaceFile) {
  $ws = Get-Content -Raw -Encoding UTF8 $workspaceFile
  $ws = Set-JsonStringProp $ws 'cmake.sourceDirectory' $wsRel
  $ws = Set-JsonStringProp $ws 'cmake.copyCompileCommands' $compile
  $ws = Set-JsonStringProp $ws 'C_Cpp.default.compileCommands' $compile
  $clangdWsArg = "--compile-commands-dir=$wsRel"
  $clangdPattern = '"clangd\.arguments"\s*:\s*\[[^\]]*\]'
  $clangdReplacement = '"clangd.arguments": [' + "`n" + '      "' + $clangdWsArg.Replace('\', '\\').Replace('"', '\"') + '"' + "`n" + '    ]'
  if ($ws -match $clangdPattern) {
    $ws = [regex]::Replace($ws, $clangdPattern, $clangdReplacement, 1)
  }
  Set-Content -Path $workspaceFile -Value $ws.TrimEnd() -Encoding UTF8 -NoNewline
  Add-Content -Path $workspaceFile -Value "`n" -Encoding UTF8
  Write-Host "OK workspace: $posixRel"
}

# 2) Examples/.vscode/settings.json
$exSettings = Join-Path $PSScriptRoot 'settings.json'
if (Test-Path $exSettings) {
  $es = Get-Content -Raw -Encoding UTF8 $exSettings
  $es = Set-JsonStringProp $es 'cmake.sourceDirectory' $exRel
  if ($es -match '"cmake\.copyCompileCommands"') {
    $es = Set-JsonStringProp $es 'cmake.copyCompileCommands' $compileEx
  }
  if ($es -match '"C_Cpp\.default\.compileCommands"') {
    $es = Set-JsonStringProp $es 'C_Cpp.default.compileCommands' $compileEx
  }
  $clangdArg = "--compile-commands-dir=$exRel"
  $clangdPattern = '"clangd\.arguments"\s*:\s*\[[^\]]*\]'
  $clangdReplacement = '"clangd.arguments": [' + "`n" + '    "' + $clangdArg.Replace('\', '\\').Replace('"', '\"') + '"' + "`n" + '  ]'
  if ($es -match $clangdPattern) {
    $es = [regex]::Replace($es, $clangdPattern, $clangdReplacement, 1)
  }
  Set-Content -Path $exSettings -Value $es.TrimEnd() -Encoding UTF8 -NoNewline
  Add-Content -Path $exSettings -Value "`n" -Encoding UTF8
  Write-Host "OK Examples/.vscode/settings.json"
}

# 3) Repo root .vscode/settings.json (ruta absoluta, por si abres la carpeta raiz)
$rootSettings = Join-Path $repoRoot '.vscode\settings.json'
$absCmake = ($cmakeDir -replace '\\', '/')
if (Test-Path $rootSettings) {
  $rs = Get-Content -Raw -Encoding UTF8 $rootSettings
  if ($rs -match '"cmake\.sourceDirectory"') {
    $rs = Set-JsonStringProp $rs 'cmake.sourceDirectory' $absCmake
    Set-Content -Path $rootSettings -Value $rs.TrimEnd() -Encoding UTF8 -NoNewline
    Add-Content -Path $rootSettings -Value "`n" -Encoding UTF8
    Write-Host "OK .vscode/settings.json (raiz)"
  }
}

Write-Host ""
Write-Host "Ejemplo activo: $posixRel"
Write-Host "Siguiente paso: Command Palette -> CMake: Delete Cache and Reconfigure"
Write-Host "Luego elige el preset (MSVC / WSL GCC-Clang) y Build."
