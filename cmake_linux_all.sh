#!/bin/sh
echo   
sh ./cmake_linux.sh Base/NoApp/Platforms/Linux/x64
sh ./cmake_linux.sh Base/TestDataIO/Platforms/Linux/x64
echo
sh ./cmake_linux.sh Console/BinConnPro/Platforms/Linux/x64
sh ./cmake_linux.sh Console/Databases/Platforms/Linux/x64
sh ./cmake_linux.sh Console/MiniWebServer/Platforms/Linux/x64
sh ./cmake_linux.sh Console/Scripts/Platforms/Linux/x64
sh ./cmake_linux.sh Console/Tests/Platforms/Linux/x64 
echo
sh ./cmake_linux.sh Graphics/Canvas2D/Platforms/Linux/x64 
sh ./cmake_linux.sh Graphics/UI_Options/Platforms/Linux/x64 
echo
