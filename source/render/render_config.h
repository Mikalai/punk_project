#ifndef _H_PUNK_RENDER_CONFIG
#define _H_PUNK_RENDER_CONFIG

#include "../config.h"

namespace Render
{
	struct PUNK_ENGINE Config
	{
		float visible_distance;
		bool use_shadows;

		Config();
	};
}

#endif	_H_PUNK_RENDER_CONFIG