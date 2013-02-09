#ifndef _H_PUNK_GPU_CONFIG
#define _H_PUNK_GPU_CONFIG

#include "../config.h"

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
		
		Config();			
	};
}

#endif	//	_H_PUNK_GPU_CONFIG