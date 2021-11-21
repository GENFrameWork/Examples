ECHO OFF
Echo Remove directorys
Echo Base
call eraseresource Base\Canvas2DDisplay
call eraseresource Base\NoApp
call eraseresource Base\TestDataIO
Echo Console
call eraseresource Console\BinConnPro
call eraseresource Console\Databases
call eraseresource Console\MiniWebServer
call eraseresource Console\Scripts
call eraseresource Console\Tests
Echo Graphics
call eraseresource Graphics\Canvas2D
call eraseresource Graphics\UI_Options
PAUSE

