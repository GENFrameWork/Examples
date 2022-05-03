echo off 
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo -------------------------------------------------------------
echo 32 Bits version
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86 > nul
call compile_windows Base\NoApp\Platforms\Windows\x86 
call compile_windows Console\BinConnPro\Platforms\Windows\x86
call compile_windows Console\Databases\Platforms\Windows\x86
call compile_windows Console\MiniWebServer\Platforms\Windows\x86
call compile_windows Console\Scripts\Platforms\Windows\x86
call compile_windows Graphics\Canvas2D\Platforms\Windows\x86 
call compile_windows Graphics\UI_Options\Platforms\Windows\x86 
echo -------------------------------------------------------------
echo 64 Bits version
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 > nul
call compile_windows Base\NoApp\Platforms\Windows\x64
call compile_windows Console\BinConnPro\Platforms\Windows\x64
call compile_windows Console\Databases\Platforms\Windows\x64
call compile_windows Console\MiniWebServer\Platforms\Windows\x64
call compile_windows Console\Scripts\Platforms\Windows\x64
call compile_windows Graphics\Canvas2D\Platforms\Windows\x64 
call compile_windows Graphics\UI_Options\Platforms\Windows\x64 
pause


