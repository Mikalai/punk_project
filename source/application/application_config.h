#ifndef _H_PUNK_APPLICATION_CONFIG
#define _H_PUNK_APPLICATION_CONFIG

#include "../gpu/gpu_config.h"
#include "../render/render_config.h"
#include "../audio/audio_config.h"
#include "../physics/physics_config.h"

namespace Punk
{
	struct Config
	{
		GPU::Config gpu_config;
		Render::Config render_config;
		Audio::Config audio_config;
		Physics::Config physics_config;
	};
}

#endif	//	_H_PUNK_APPLICATION_CONFIG