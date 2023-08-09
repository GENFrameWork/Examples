@echo off
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo -------------------------------------------------------------
for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "start_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)
..\Utilities\printf\printf "Start process ... \n\n"
echo %DATE% %TIME% > Output.txt
..\Utilities\printf\printf "Examples Windows PC x32 ...\n"
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
..\Utilities\printf\printf "Examples Base Windows PC x32 ...\n"
call ./../GEN/Batch/compile_windows.bat Base/NotAppExample/Platforms/Windows /x32 notappexample
call ./../GEN/Batch/compile_windows.bat Base/AppBaseExample/Platforms/Windows /x32 appbaseexample
call ./../GEN/Batch/compile_windows.bat Base/MemCtrlExample/Platforms/Windows /x32 memctrlexample

..\Utilities\printf\printf "Examples Console Windows PC x32 ...\n"
call ./../GEN/Batch/compile_windows.bat Console/BinConnPro/Platforms/Windows /x32 binconnpro
call ./../GEN/Batch/compile_windows.bat Console/Databases/Platforms/Windows /x32 databases
call ./../GEN/Batch/compile_windows.bat Console/MiniWebServer/Platforms/Windows /x32 miniwebserver
call ./../GEN/Batch/compile_windows.bat Console/Scripts/Platforms/Windows /x32 scripts 

..\Utilities\printf\printf "Examples Graphics Windows PC x32 ...\n"
call ./../GEN/Batch/compile_windows.bat Graphics/Canvas2D/Platforms/Windows /x32 canvas2d
call ./../GEN/Batch/compile_windows.bat Graphics/UI_Options/Platforms/Windows /x32 ui_options

..\Utilities\printf\printf "Examples Windows PC x64 ...\n"
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 
..\Utilities\printf\printf "Examples Base Windows PC x64 ...\n"
call ./../GEN/Batch/compile_windows.bat Base/NotAppExample/Platforms/Windows /x64 notappexample
call ./../GEN/Batch/compile_windows.bat Base/AppBaseExample/Platforms/Windows /x64 appbaseexample
call ./../GEN/Batch/compile_windows.bat Base/MemCtrlExample/Platforms/Windows /x64 memctrlexample

..\Utilities\printf\printf "Examples Console Windows PC x64 ...\n"
call ./../GEN/Batch/compile_windows.bat Console/BinConnPro/Platforms/Windows /x64 binconnpro
call ./../GEN/Batch/compile_windows.bat Console/Databases/Platforms/Windows /x64 databases
call ./../GEN/Batch/compile_windows.bat Console/MiniWebServer/Platforms/Windows /x64 miniwebserver
call ./../GEN/Batch/compile_windows.bat Console/Scripts/Platforms/Windows /x64 scripts 

..\Utilities\printf\printf "Examples Graphics Windows PC x64 ...\n"
call ./../GEN/Batch/compile_windows.bat Graphics/Canvas2D/Platforms/Windows /x64 canvas2d
call ./../GEN/Batch/compile_windows.bat Graphics/UI_Options/Platforms/Windows /x64 ui_options

for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "end_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)

set /a "elapsed_time=end_time - start_time"

set /a "hours=elapsed_time / 360000"
set /a "minutes=(elapsed_time %% 360000) / 6000"
set /a "seconds=(elapsed_time %% 6000) / 100"

..\Utilities\printf\printf "End process.\nProcessing time: %02d:%02d:%02d\n"  %hours% %minutes% %seconds%