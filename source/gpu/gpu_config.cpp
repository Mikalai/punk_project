#include "gpu_config.h"

namespace Gpu
{
	Config::Config()   
        : disable_3d_graphics(false)
        , view_width(1024)
		, view_height(768)
		, view_left(100)
		, view_top(100)
		, fullscreen(false)
		, refresh_rate(60)
		, bits_per_pixel(32)
        , shadow_map_width(4096)
        , shadow_map_height(4096)
        , use_multisampling(true)
        , multisampling_depth(2)
        , use_coveragesampling(true)
        , coverage_depth(4)
	{}
}
