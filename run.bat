@echo off
del /Q bin\hopital.exe 2>nul
gcc src/*.c menu/*.c -I include -o bin/hopital.exe -Wall
if %errorlevel% neq 0 exit /b
.\bin\hopital.exe
pause