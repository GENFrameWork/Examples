ECHO Off
ECHO Generate Project ...
rmdir %1 /s /q
mkdir %1
cd /d %1
cmake -G "Ninja" -DTARGET=pc ../..
ECHO Compile ...
ninja
cd /d ../../../../../