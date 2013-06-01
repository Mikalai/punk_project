start /WAIT prepare.cmd
 
mkdir project
cd .\project
mkdir punk_project_codelite
cd .\punk_project_codelite

copy  ..\..\premake4.exe 
copy  ..\..\premake4.lua

premake4.exe codelite

del premake4.exe
del premake4.lua

cd ..\..\