
mkdir .\source\3rd

::
::	COPY JPEG LIB 
::
mkdir .\source\3rd\jpeg
set SRC=.\3rd\src\jpeg-8d
set DST=.\source\3rd\jpeg

copy %SRC%\*.h %DST%\* 
copy %SRC%\*.c %DST%\*
copy %SRC%\jconfig.vc %DST%\jconfig.h

::
::	COPY BULLET LIB
::
mkdir .\source\3rd\bullet
set SRC=.\3rd\src\bullet-2.81
set DST=.\source\3rd\bullet

xcopy /E /Y %SRC%\* %DST%\*

::
::	COPY OPENAL LIB
::
mkdir .\source\3rd\openal
set SRC=.\3rd\src\openal
set DST=.\source\3rd\openal

xcopy /E /Y %SRC%\* %DST%\*
 
::
:: 	COPY VORBIS CODEC
::
mkdir .\source\3rd\vorbis
set SRC=.\3rd\src\vorbis
set DST=.\source\3rd\vorbis

xcopy /E /Y %SRC%\* %DST%\*

::
:: 	COPY VORBIS CODEC
::
mkdir .\source\3rd\ogg
set SRC=.\3rd\src\libogg\include\ogg
set DST=.\source\3rd\ogg

xcopy /E /Y %SRC%\*.h %DST%\*.h
copy %SRC%\config_types.h.in %DST%\config_types.h

set SRC=.\3rd\src\libogg\src
xcopy /E /Y %SRC%\*.c %DST%\*
 
::
::	COPY LIBVORBS 
::
mkdir .\source\3rd\libvorbis
set SRC=.\3rd\src\libvorbis\lib
set DST=.\source\3rd\libvorbis

xcopy /E /Y %SRC%\* %DST%\*

::	override ogg and vorbis with files in libvorbis
set SRC=.\3rd\src\libvorbis\include
set DST=.\source\3rd

xcopy /E /Y %SRC%\* %DST%\*

::
::	COPY OPENCL
::
mkdir .\source\3rd\cl
::	this from nvidia opencl sdk. Other vendors supposed to have different path i think
set SRC=.\3rd\src\OpenCL\common\inc\CL
set DST=.\source\3rd\cl

xcopy /E /Y %SRC%\* %DST%\*

::
::	COPY LIBPNG
::
mkdir .\source\3rd\png
set SRC=.\3rd\src\libpng
set DST=.\source\3rd\png

copy %SRC%\*.h %DST%\* 
copy %SRC%\*.c %DST%\*

xcopy /E /Y %SRC%\contrib\visupng\* %DST%\contrib\visupng\*

::
::	COPY LIB NOISE
::
mkdir .\source\3rd\noise
set SRC=.\3rd\src\libnoise\noise\src
set DST=.\source\3rd\noise

xcopy /E /Y %SRC%\* %DST%\*

::
::	COPY FREETYPE
::
mkdir .\source\3rd\freetype
set SRC=.\3rd\src\freetype\include
set DST=.\source\3rd\freetype\

xcopy /E /Y %SRC%\* %DST%\*

set SRC=.\3rd\src\freetype\src

xcopy /E /Y %SRC%\* %DST%\*

exit