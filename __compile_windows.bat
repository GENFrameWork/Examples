@echo off
set "ACTUALPATH=%CD%"
..\Utilities\CompileBuilder\Platforms\Windows\x32\compilerbuilder %ACTUALPATH%
PAUSE
