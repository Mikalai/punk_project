#include "gpu_config.h"

namespace GPU
{
	Config::Config()
		: view_width(1024)
		, view_height(768)
		, view_left(100)
		, view_top(100)
		, fullscreen(false)
		, refresh_rate(60)
		, bits_per_pixel(32)
	{}
}