start /WAIT prepare.cmd

mkdir project
cd .\project
mkdir punk_projects_vc2012
cd .\punk_projects_vc2012

copy  ..\..\premake4.exe 
copy  ..\..\premake4.lua

premake4.exe vs2010

del premake4.exe
del premake4.lua

cd ..\..\