ECHO OFF
Echo Remove directorys
Echo Base
call ..\GEN\Batch\erase_artifacts Base\Canvas2DDisplay
call ..\GEN\Batch\erase_artifacts Base\NoApp
call ..\GEN\Batch\erase_artifacts Base\TestDataIO
Echo Console
call ..\GEN\Batch\erase_artifacts Console\BinConnPro
call ..\GEN\Batch\erase_artifacts Console\Databases
call ..\GEN\Batch\erase_artifacts Console\MiniWebServer
call ..\GEN\Batch\erase_artifacts Console\Scripts
call ..\GEN\Batch\erase_artifacts Console\Tests
Echo Graphics
call ..\GEN\Batch\erase_artifacts Graphics\Canvas2D
call ..\GEN\Batch\erase_artifacts Graphics\UI_Options
PAUSE

