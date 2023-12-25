@echo off

echo Choose an IDE to build:
echo 1. vs2022
echo 2. vs2019
echo 3. vs2017
echo 4. vs2015
echo 5. vs2013
echo 6. vs2012
echo 7. vs2010
echo 8. vs2008
echo 9. vs2005
echo 10. gmake
echo 11. gmake2
echo 12. xcode4
echo 13. codelite

set /p choice="Enter your choice (e.g., 1 for vs2022): "

:: Define an array of IDE options
set "ide[1]=vs2022"
set "ide[2]=vs2019"
set "ide[3]=vs2017"
set "ide[4]=vs2015"
set "ide[5]=vs2013"
set "ide[6]=vs2012"
set "ide[7]=vs2010"
set "ide[8]=vs2008"
set "ide[9]=vs2005"
set "ide[10]=gmake"
set "ide[11]=gmake2"
set "ide[12]=xcode4"
set "ide[13]=codelite"

:: Get the selected IDE from the array
if "%choice%" gtr "0" if "%choice%" lss "14" (
    Scripts\Binaries\Premake\Windows\premake5.exe --file=Build.lua !ide[%choice%]!
) else (
    echo Invalid choice! Exiting...
    exit /b
)

echo Premake setup completed!

%LOCALAPPDATA%\Microsoft\WindowsApps\python3.12.exe Scripts/setup.py

echo Setup completed!
