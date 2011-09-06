/*
	File: Window.h
	Author: Abramov Nickolai
	Description: Wrapper around os api
*/

#ifndef _H_WINDOW
#define _H_WINDOW

#ifdef _WIN32
#include "win32/window_win32.h"
#endif

#ifdef __linux__
#include "linux/window_linux.h"
#endif

#endif	//_H_WINDOW
