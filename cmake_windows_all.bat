echo off    
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
echo
call cmake_windows Base\NoApp\Platforms\Windows\x86
call cmake_windows Base\TestDataIO\Platforms\Windows\x86
echo
call cmake_windows Console\BinConnPro\Platforms\Windows\x86
call cmake_windows Console\Databases\Platforms\Windows\x86
call cmake_windows Console\MiniWebServer\Platforms\Windows\x86
call cmake_windows Console\Scripts\Platforms\Windows\x86
call cmake_windows Console\Tests\Platforms\Windows\x86 
echo
call cmake_windows Graphics\Canvas2D\Platforms\Windows\x86 
call cmake_windows Graphics\UI_Options\Platforms\Windows\x86 
echo
echo off    
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64
echo
call cmake_windows Base\NoApp\Platforms\Windows\x64
call cmake_windows Base\TestDataIO\Platforms\Windows\x64
echo
call cmake_windows Console\BinConnPro\Platforms\Windows\x64
call cmake_windows Console\Databases\Platforms\Windows\x64
call cmake_windows Console\MiniWebServer\Platforms\Windows\x64
call cmake_windows Console\Scripts\Platforms\Windows\x64
call cmake_windows Console\Tests\Platforms\Windows\x64 
echo
call cmake_windows Graphics\Canvas2D\Platforms\Windows\x64 
call cmake_windows Graphics\UI_Options\Platforms\Windows\x64 
echo
pause



