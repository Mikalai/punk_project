#include "openal/al_sound_system_impl.h"

namespace Audio
{
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