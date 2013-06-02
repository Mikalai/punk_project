#ifndef _H_PUNK_AUDIO_CONFIG
#define _H_PUNK_AUDIO_CONFIG

#include "../config.h"

namespace Audio
{
	struct PUNK_ENGINE_API Config
	{
		int ambient_volume;
		int music_volume;
		int voice_volume;
		int shoot_volume;

		Config();
	};
}

#endif	//	_H_PUNK_AUDIO_CONFIG