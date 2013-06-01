#ifndef _H_PUNK_AUDIO_OPENAL_SOUND_SYSTEM
#define _H_PUNK_AUDIO_OPENAL_SOUND_SYSTEM

#ifdef USE_OPENAL

#include "openal.h"
#include "../sound_system.h"

namespace Audio
{
	struct SoundSystemImpl
	{
		ALboolean m_eax_support;

		void Initialize();
		~SoundSystemImpl();
		void SetSoundSpeed(float value);
		float GetSoundSpeed() const;
		void SetDopplerFactor(float value);
		float GetDopplerFactor() const;
		void SetDistanceModel(DistanceModel value);
		DistanceModel GetDistanceModel();
	};
}

#endif  //  USE_OPENAL

#endif	//	_H_PUNK_AUDIO_OPENAL_SOUND_SYSTEM
