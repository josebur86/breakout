@echo off
setlocal

rem Generate CTags file
ctags -R .

rem Build
set OutDir=.

cl /nologo /Zi /EHsc code\main.cpp /link /subsystem:CONSOLE third_party\SDL2\lib\x64\SDL2main.lib third_party\SDL2\lib\x64\SDL2.lib

xcopy /Y third_party\SDL2\lib\x64\SDL2.dll %OutDir%

endlocal
