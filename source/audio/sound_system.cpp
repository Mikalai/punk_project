#include "openal/openal.h"
#include "sound_system.h"

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

	void SoundSystemImpl::Initialize()
	{
		auto device = alcOpenDevice(nullptr); 		
		if (device) {
			auto context = alcCreateContext(device, nullptr);
			alcMakeContextCurrent(context);
		}
		// Check for EAX 2.0 support
		m_eax_support = alIsExtensionPresent("EAX2.0"); 
	}

	SoundSystemImpl::~SoundSystemImpl()
	{
		auto context = alcGetCurrentContext();
		auto device = alcGetContextsDevice(context);
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device); 
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

	SoundSystem::SoundSystem()
		: impl(new SoundSystemImpl)
	{}

	SoundSystem::~SoundSystem()
	{
		Destroy();
	}

	void SoundSystem::Initialize()
	{
		impl->Initialize();
	}

	void SoundSystem::Destroy()
	{
		delete impl;
		impl = nullptr;
	}

	void SoundSystem::SetSoundSpeed(float value)
	{
		impl->SetSoundSpeed(value);
	}

	float SoundSystem::GetSoundSpeed() const
	{
		return impl->GetSoundSpeed();
	}

	void SoundSystem::SetDopplerFactor(float value)
	{
		impl->SetDopplerFactor(value);
	}

	float SoundSystem::GetDopplerFactor() const
	{
		return impl->GetDopplerFactor();
	}

	void SoundSystem::SetDistanceModel(DistanceModel value)
	{
		impl->SetDistanceModel(value);
	}

	DistanceModel SoundSystem::GetDistanceModel()
	{
		return impl->GetDistanceModel();
	}
}