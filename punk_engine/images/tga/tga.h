/*********************************************************************NVMH1****
File:
nv_tga.h

Copyright (C) 1999, 2000 NVIDIA Corporation
This file is provided without support, instruction, or implied warranty of any
kind.  NVIDIA makes no guarantee of its fitness for a particular purpose and is
not liable under any circumstances for any damages or loss whatsoever arising
from the use or inability to use this file or items derived from it.

Comments:


******************************************************************************/

#ifndef __nv_tga_h__
#define __nv_tga_h__

//#include <GL/gl.h>

namespace ImageLoader
{
	extern void gliReadTGA(FILE *fp, const char *name, ImageFile* ImageFile);
}

#endif /* __nv_tga_h__ */
