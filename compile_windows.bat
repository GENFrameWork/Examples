echo Generate Project: %1%
if exist %1 (rmdir %1 /s /q)
mkdir %1
cd /d %1
cmake -G "Ninja" -DTARGET=pc ../.. 
ninja
cd /d ../../../../../
