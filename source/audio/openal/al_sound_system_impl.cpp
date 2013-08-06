#ifdef USE_OPENAL

#include "al_sound_system_impl.h"

namespace Audio
{
	void SoundSystemImpl::Initialize()
	{
		Init();
		//auto device = alcOpenDevice(nullptr);
		//if (device) {
		//	auto context = alcCreateContext(device, nullptr);
		//	alcMakeContextCurrent(context);
		//}
		// Check for EAX 2.0 support
		m_eax_support = alIsExtensionPresent("EAX2.0");
	}

	SoundSystemImpl::~SoundSystemImpl()
	{
		//auto context = alcGetCurrentContext();
		//auto device = alcGetContextsDevice(context);
		//alcMakeContextCurrent(nullptr);
		//alcDestroyContext(context);
		//alcCloseDevice(device);
		Destroy();
	}

	void SoundSystemImpl::SetSoundSpeed(float value)
	{
		alSpeedOfSound(static_cast<ALfloat>(value));
		ValidateOpenAL(L"Can't set sound speed");
	}

	float SoundSystemImpl::GetSoundSpeed() const
	{
		ALfloat value = alGetFloat(AL_SPEED_OF_SOUND);
		ValidateOpenAL(L"Can't get sound speed");
		return static_cast<float>(value);
	}

	void SoundSystemImpl::SetDopplerFactor(float value)
	{
		alDopplerFactor(value);
		ValidateOpenAL(L"Can't set doppler factor");
	}

	float SoundSystemImpl::GetDopplerFactor() const
	{
		ALfloat value = alGetFloat(AL_DOPPLER_FACTOR);
		ValidateOpenAL(L"Can't get doppler factor");
		return static_cast<float>(value);
	}

	void SoundSystemImpl::SetDistanceModel(DistanceModel value)
	{
		alDistanceModel(DistanceModelToOpenALDistanceModel(value));
		ValidateOpenAL(L"Can't set distance model");
	}

	DistanceModel SoundSystemImpl::GetDistanceModel()
	{
		ALint value = alGetInteger(AL_DISTANCE_MODEL);
		ValidateOpenAL(L"Can't get distance model");
		return OpenALDistanceModelToDistanceModel(value);
	}
}

#endif // USE_OPENAL
