
#include "../math/vec3.h"

#ifdef USE_OPENAL
#define HAS_AUDIO_SOURCE
#include "openal/al_source_impl.h"
#else
#include "audio_source.h"
#endif // USE_OPENAL

namespace Audio
{
	Source::Source()
	#ifdef HAS_AUDIO_SOURCE
		: impl(new SourceImpl)
    #else
        : impl(nullptr)
    #endif
	{}

	Source::~Source()
	{
		delete impl;
		impl = nullptr;
	}

	void Source::SetPitch(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetPitch(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetPitch() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetPitch();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetGain(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetGain(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetGain() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetGain();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetMinGain(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetMinGain(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetMinGain() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetMinGain();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetMaxGain(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetMaxGain(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetMaxGain() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetMaxGain();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetRolloffFactor(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetRolloffFactor(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetRolloffFactor() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetRolloffFactor();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetMaxDistance(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetMaxDistance(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetMaxDistance() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetMaxDistance();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetConeOuterGain(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetConeOuterGain(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetConeOuterGain() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetConeOuterGain();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetConeInnerAngle(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetConeInnerAngle(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetConeInnerAngle() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetConeInnerAngle();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetConeOuterAngle(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetConeOuterAngle(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetConeOuterAngle() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetConeOuterAngle();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetReferenceDistance(float value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetReferenceDistance(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	float Source::GetReferenceDistance() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetReferenceDistance();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetPosition(float x, float y, float z)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetPosition(Math::vec3(x, y, z));
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetPosition(const Math::vec3& value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetPosition(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	const Math::vec3 Source::GetPosition() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetPosition();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetVelocity(float x, float y, float z)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetVelocity(Math::vec3(x, y, z));
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetVelocity(const Math::vec3& value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetVelocity(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	const Math::vec3 Source::GetVelocity() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetVelocity();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetDirection(float x, float y, float z)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetDirection(Math::vec3(x, y, z));
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetDirection(const Math::vec3& value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetDirection(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	const Math::vec3 Source::GetDirection() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->GetDirection();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetRelative(bool value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetRelative(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsRelative() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->IsRelative();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetLooping(bool value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetLooping(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsLooping() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->IsLooping();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::SetBuffer(Buffer* value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->SetBuffer(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::EnqueBuffer(Buffer* value)
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->EnqueBuffer(value);
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::Play()
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->Play();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsPlaying() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->IsPlaying();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::Pause()
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->Pause();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsPaused() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->IsPaused();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::Stop()
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->Stop();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsStopped() const
	{
	    #ifdef HAS_AUDIO_SOURCE
		return impl->IsStopped();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	bool Source::IsActive() const
	{
	    #ifdef HAS_AUDIOS_SOURCE
		return impl->IsActive();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}

	void Source::Reset()
	{
	    #ifdef HAS_AUDIO_SOURCE
		impl->Reset();
		#else
		throw System::PunkException(L"Audio source is not available");
		#endif
	}
}
