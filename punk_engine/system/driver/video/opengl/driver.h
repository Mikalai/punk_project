/*
File: Driver.h
Author: Abramau Mikalai
Description: Contains an entity that must initialise OpenGL
and handle different parameters about users video system
*/

#ifndef _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER
#define _H_PUNK_DRIVER_VIDEO_OPENGL_DRIVER

#ifdef _WIN32
#include "win32/driver_win32.h"
#include "shader_program.h"
#include "render_context\render_context.h"
#include "render_context\rc_solid_color_3d.h"
#include "texture_context.h"
#include "vertex_array_object.h"
#include "text_texture_2d.h"
#include "module.h"
#endif

#ifdef __linux__
#include 
#endif

#endif