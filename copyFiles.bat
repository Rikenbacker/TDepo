@echo off
rem Копирую dll
mkdir "%2bin"
rem del "%2bin\*" /Q
copy "%1..\ogreBuild\sdk\bin\%3\*.dll" "%2bin\"
if "%3" == "Debug" (
copy "%1..\ogreBuild\sdk\bin\%3\*.pdb" "%2bin\"
)

rem Копирую и заменяю в завимимости от типа сборки настройки
call :CopyDirectory %1 %2 config
call :RenameDebugFiles %2config\ %3
call :DeleteDebugFiles %2config\

rem Создаю папку с логами
mkdir "%2logs"
del %2logs\* /Q

rem Копирую папку с ресурсами
call :CopyDirectory %1 %2 data
call :CopyDirectory %1 %2 data\materials
call :CopyDirectory %1 %2 data\materials\script
call :CopyDirectory %1 %2 data\materials\textures

call :CopyDirectory %1 %2 data\models

goto end

:RenameDebugFiles
if "%2" == "Debug" (
for %%i in ("%1*_Debug.*") do (
call :RenameFile %%~ni %%~xi %2 %1
echo %%i
)
)
if "%2" == "Release" (
for %%i in ("%1*_Release.*") do (
call :RenameFile %%~ni %%~xi %2 %1
echo %%i
)
)
exit /B 0

:DeleteDebugFiles
del %1*_Debug.*
del %1*_Release.*
exit /B 0

:RenameFile
set zz=%1
if "%3" == "Debug" (
set zz=%zz:_Debug=_%
)
if "%3" == "Release" (
set zz=%zz:_Release=_%
)
set zz=%zz:~0,-1%

ren %4%1%2 %zz%%2

exit /B 0

:CopyDirectory
mkdir "%2%3"
del %2%3\* /Q
copy "%1%3\*" "%2%3"
exit /B 0


:end