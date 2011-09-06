/*
File: Driver.h
Author: Abramov Nickolai
Description: Contains an entity that must initialise OpenGL
and handle different parameters about users video system
*/

#ifndef _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER
#define _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER

#ifdef _WIN32
#include "win32/driver_win32.h"
#include "camera.h"
#include "shader_program.h"
#include "render_context.h"
#include "texture_context.h"
#include "vertex_array_object.h"
#endif

#ifdef __linux__
#include 
#endif

#endif