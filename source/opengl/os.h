/*
	File: OS.h
	Author: Abramau Mikalai
	Description: Contains operating system specific headers
*/

#ifndef _OS_H
#define _OS_H

#ifdef __linux__
//#include <gl3/glxext.h>
#endif

#ifdef _WIN32
#include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <limits>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <exception>
#include <string>

#ifdef _DEBUG
#define GL_CHECK_ERROR(what) if (glGetError() != GL_NO_ERROR) throw std::runtime_error(what);
#else
#define GL_CHECK_ERROR
#endif



#include "nvtristrip/nv_tri_strip.h"

#endif	//	_OS_H
