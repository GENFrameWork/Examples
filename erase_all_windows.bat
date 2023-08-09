echo off
echo Remove directorys
echo Base
call ..\GEN\Batch\erase_artifacts Base\NotAppExample
call ..\GEN\Batch\erase_artifacts Base\AppBaseExample
call ..\GEN\Batch\erase_artifacts Base\Canvas2DDisplay
call ..\GEN\Batch\erase_artifacts Base\MemCtrlExample
echo Console
call ..\GEN\Batch\erase_artifacts Console\BinConnPro
call ..\GEN\Batch\erase_artifacts Console\Databases
call ..\GEN\Batch\erase_artifacts Console\MiniWebServer
call ..\GEN\Batch\erase_artifacts Console\Scripts
call ..\GEN\Batch\erase_artifacts Console\Tests
echo Graphics
call ..\GEN\Batch\erase_artifacts Graphics\Canvas2D
call ..\GEN\Batch\erase_artifacts Graphics\UI_Options
pause

