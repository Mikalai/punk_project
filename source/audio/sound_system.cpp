
#ifdef USE_OPENAL
#define HAS_AUDIO_SYSTEM
#include "openal/al_sound_system_impl.h"
#else
#include "sound_system.h"
#include "../system/errors/module.h"
#endif

namespace Audio
{
	SoundSystem::SoundSystem()
	#ifdef HAS_AUDIO_SYSTEM
		: impl(new SoundSystemImpl)
    #else
        : impl(nullptr)
    #endif
	{}

	SoundSystem::~SoundSystem()
	{
		Destroy();
	}

	void SoundSystem::Initialize()
	{
	    #ifdef HAS_AUDIO_SYSTEM
		impl->Initialize();
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	void SoundSystem::Destroy()
	{
	    #ifdef HAS_AUDIO_SYSTEM
		delete impl;
		impl = nullptr;
		#endif
	}

	void SoundSystem::SetSoundSpeed(float value)
	{
	    #ifdef HAS_AUDIO_SYSTEM
		impl->SetSoundSpeed(value);
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	float SoundSystem::GetSoundSpeed() const
	{
	    #ifdef HAS_AUDIO_SYSTEM
		return impl->GetSoundSpeed();
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	void SoundSystem::SetDopplerFactor(float value)
	{
	    #ifdef HAS_AUDIO_SYSTEM
		impl->SetDopplerFactor(value);
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	float SoundSystem::GetDopplerFactor() const
	{
	    #ifdef HAS_AUDIO_SYSTEM
		return impl->GetDopplerFactor();
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	void SoundSystem::SetDistanceModel(DistanceModel value)
	{
	    #ifdef HAS_AUDIO_SYSTEM
		impl->SetDistanceModel(value);
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}

	DistanceModel SoundSystem::GetDistanceModel()
	{
	    #ifdef HAS_AUDIO_SYSTEM
		return impl->GetDistanceModel();
		#else
		throw System::PunkException(L"Sound system is not available");
		#endif
	}
}
