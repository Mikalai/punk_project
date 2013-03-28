#ifndef _H_PUNK_AUDIO_OPENAL_DISTANCE_MODLES
#define _H_PUNK_AUDIO_OPENAL_DISTANCE_MODLES

#include "../audio_distance_model.h"
#include "openal.h"

namespace Audio
{
	extern ALint DistanceModelToOpenALDistanceModel(DistanceModel value);
	extern DistanceModel OpenALDistanceModelToDistanceModel(ALenum value);
}

#endif	//	_H_PUNK_AUDIO_OPENAL_DISTANCE_MODLES