prepare.cmd

mkdir project
cd .\project
mkdir punk_projects_codeblocks
cd .\punk_projects_codeblocks

copy  ..\..\premake4.exe 
copy  ..\..\premake4.lua

premake4.exe codeblocks

del premake4.exe
del premake4.lua

cd ..\..\