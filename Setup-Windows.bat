@echo off

echo Choose an IDE to build:
echo vs2022
echo vs2019
echo vs2017
echo vs2015
echo vs2013
echo vs2012
echo vs2010
echo vs2008
echo vs2005
echo gmake
echo gmake2
echo xcode4
echo codelite

set /p choice="Enter your choice (e.g., 1 for vs2022): "


:: Get the selected IDE from the array
call premake5 --file=Build.lua %choice%

echo Premake setup completed!

:: Pause the script to see the output before closing
pause