#!/bin/sh
echo   
sh ./compile_linux.sh Base/NoApp/Platforms/Linux/x64
echo
sh ./compile_linux.sh Console/BinConnPro/Platforms/Linux/x64
sh ./compile_linux.sh Console/Databases/Platforms/Linux/x64
sh ./compile_linux.sh Console/MiniWebServer/Platforms/Linux/x64
sh ./compile_linux.sh Console/Scripts/Platforms/Linux/x64
echo
sh ./compile_linux.sh Graphics/Canvas2D/Platforms/Linux/x64 
sh ./compile_linux.sh Graphics/UI_Options/Platforms/Linux/x64 
echo
