start /WAIT prepare.cmd

mkdir project
cd .\project
mkdir punk_projects_qt
cd .\punk_projects_qt

copy  ..\..\qt-support.lua
copy  ..\..\premake4.exe 
copy  ..\..\premake4.lua
copy  ..\..\vcproj2cmake.ps1

premake4.exe vs2005

powershell .\vcproj2cmake.ps1 .\punk_project.vcproj conf="Debug"
del premake4.exe
del premake4.lua
del qt-support.lua
del vcproj2cmake.ps1

cd ..\..\