@echo off
rem set VSLANG = 1033
if not defined INCLUDE call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
echo %1
make
@REM cl.exe /?


