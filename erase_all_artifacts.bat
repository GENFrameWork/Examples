ECHO OFF
Echo Remove directorys
Echo Base
call erase_artifacts Base\Canvas2DDisplay
call erase_artifacts Base\NoApp
call erase_artifacts Base\TestDataIO
Echo Console
call erase_artifacts Console\BinConnPro
call erase_artifacts Console\Databases
call erase_artifacts Console\MiniWebServer
call erase_artifacts Console\Scripts
call erase_artifacts Console\Tests
Echo Graphics
call erase_artifacts Graphics\Canvas2D
call erase_artifacts Graphics\UI_Options
PAUSE

