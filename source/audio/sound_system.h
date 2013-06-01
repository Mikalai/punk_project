#ifndef _H_PUNK_AUDIO_SOUND_SYSTEM
#define _H_PUNK_AUDIO_SOUND_SYSTEM

#include "../config.h"
#include "audio_distance_model.h"

namespace Audio
{
	struct SoundSystemImpl;

	class PUNK_ENGINE_PUBLIC SoundSystem final
	{
	public:
		SoundSystem();
		~SoundSystem();		

		void Initialize();
		void Destroy();
		void SetSoundSpeed(float value);
		float GetSoundSpeed() const;
		void SetDopplerFactor(float value);
		float GetDopplerFactor() const;
		void SetDistanceModel(DistanceModel value);
		DistanceModel GetDistanceModel();
		SoundSystemImpl* impl;

	private:
		//	VS12 doesn't support '= delete'
		SoundSystem(const SoundSystem&);
		SoundSystem(const SoundSystem&&);
		SoundSystem& operator = (const SoundSystem&);
		SoundSystem& operator = (const SoundSystem&&);
	};
}

#endif	//	_H_PUNK_AUDIO_SOUND_SYSTEM