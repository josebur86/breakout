@echo off
setlocal

rem Generate CTags file
ctags -R .

rem Build
set OutDir=.

REM Generate Open GL
cl /nologo /Zi code\generate_gl_init.cpp
generate_gl_init.exe

cl /nologo /Zi /EHsc /I third_party\SDL2\include code\main.cpp /link /subsystem:CONSOLE third_party\SDL2\lib\x64\SDL2main.lib third_party\SDL2\lib\x64\SDL2.lib opengl32.lib

xcopy /Y third_party\SDL2\lib\x64\SDL2.dll %OutDir%

endlocal
