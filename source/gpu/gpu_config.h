#ifndef _H_PUNK_GPU_CONFIG
#define _H_PUNK_GPU_CONFIG

#ifdef _WIN32
#include <windows.h>
#endif

#include "../config.h"

#define PUNK_GPU_USE_OPENGL

namespace GPU
{
	struct PUNK_ENGINE Config
	{
		int view_width;
		int view_height;
		int view_left;
		int view_top;
		bool fullscreen;
		int refresh_rate;
		int bits_per_pixel;
        int shadow_map_width;
        int shadow_map_height;

#ifdef _WIN32
        HWND m_hwnd;
#endif
		
		Config();			
	};
}

#endif	//	_H_PUNK_GPU_CONFIG
