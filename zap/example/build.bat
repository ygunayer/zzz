REM This script compiles the program and runs it
CALL vcvars64.bat
mkdir bin 2>nul
  cl.exe main.c /Fe"bin/" /Fo"bin/" /link user32.lib
.\bin\main.exe