/*
File: Driver.h
Author: Abramau Mikalaj
Description: Contains an entity that must initialise OpenGL
and handle different parameters about users video system
*/

#ifndef _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER
#define _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER

#ifdef _WIN32
#include "win32\driver_win32.h"
#include "renderable\renderable_data.h"
#include "render\render.h"
#include "render_context\render_contexts.h"
#include "textures\textures.h"
#endif

#ifdef __linux__
#include 
#endif

#endif