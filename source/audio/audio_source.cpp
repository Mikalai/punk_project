#include "../math/vec3.h"
#include "openal/al_source_impl.h"

namespace Audio
{
	void Source::SetPitch(float value)
	{
		impl->SetPitch(value);
	}

	float Source::GetPitch() const
	{
		return impl->GetPitch();
	}

	void Source::SetGain(float value)
	{
		impl->SetGain(value);
	}

	float Source::GetGain() const
	{
		return impl->GetGain();
	}

	void Source::SetMinGain(float value)
	{
		impl->SetMinGain(value);
	}

	float Source::GetMinGain() const
	{
		return impl->GetMinGain();
	}

	void Source::SetMaxGain(float value)
	{
		impl->SetMaxGain(value);
	}

	float Source::GetMaxGain() const
	{
		return impl->GetMaxGain();
	}

	void Source::SetRolloffFactor(float value)
	{
		impl->SetRolloffFactor(value);
	}

	float Source::GetRolloffFactor() const
	{
		return impl->GetRolloffFactor();
	}

	void Source::SetMaxDistance(float value)
	{
		impl->SetMaxDistance(value);
	}

	float Source::GetMaxDistance() const
	{
		return impl->GetMaxDistance();
	}

	void Source::SetConeOuterGain(float value)
	{
		impl->SetConeOuterGain(value);
	}

	float Source::GetConeOuterGain() const
	{
		return impl->GetConeOuterGain();
	}

	void Source::SetConeInnerAngle(float value)
	{
		impl->SetConeInnerAngle(value);
	}

	float Source::GetConeInnerAngle() const
	{
		return impl->GetConeInnerAngle();
	}

	void Source::SetConeOuterAngle(float value)
	{
		impl->SetConeOuterAngle(value);
	}

	float Source::GetConeOuterAngle() const
	{
		return impl->GetConeOuterAngle();
	}

	void Source::SetReferenceDistance(float value)
	{
		impl->SetReferenceDistance(value);
	}

	float Source::GetReferenceDistance() const
	{
		return impl->GetReferenceDistance();
	}

	void Source::SetPosition(float x, float y, float z)
	{
		impl->SetPosition(Math::vec3(x, y, z));
	}

	void Source::SetPosition(const Math::vec3& value)
	{
		impl->SetPosition(value);
	}

	const Math::vec3 Source::GetPosition() const
	{
		return impl->GetPosition();
	}

	void Source::SetVelocity(float x, float y, float z)
	{
		impl->SetVelocity(Math::vec3(x, y, z));
	}

	void Source::SetVelocity(const Math::vec3& value)
	{
		impl->SetVelocity(value);
	}

	const Math::vec3 Source::GetVelocity() const
	{
		return impl->GetVelocity();
	}

	void Source::SetDirection(float x, float y, float z)
	{
		impl->SetDirection(Math::vec3(x, y, z));
	}

	void Source::SetDirection(const Math::vec3& value)
	{
		impl->SetDirection(value);
	}

	const Math::vec3 Source::GetDirection() const
	{
		return impl->GetDirection();
	}

	void Source::SetRelative(bool value)
	{
		impl->SetRelative(value);
	}

	bool Source::IsRelative() const
	{
		return impl->IsRelative();
	}

	void Source::SetLooping(bool value)
	{
		impl->SetLooping(value);
	}

	bool Source::IsLooping() const
	{
		return impl->IsLooping();
	}

	void Source::SetBuffer(Buffer* value)
	{
		impl->SetBuffer(value);
	}

	void Source::EnqueBuffer(Buffer* value)
	{
		impl->EnqueBuffer(value);
	}

	void Source::Play()
	{
		impl->Play();
	}

	bool Source::IsPlaying() const
	{
		return impl->IsPlaying();
	}

	void Source::Pause()
	{
		return impl->Pause();
	}

	bool Source::IsPaused() const
	{
		return impl->IsPaused();
	}

	void Source::Stop()
	{
		impl->Stop();
	}

	bool Source::IsStopped() const
	{
		return impl->IsStopped();
	}

	bool Source::IsActive() const
	{
		return impl->IsActive();
	}

	void Source::Reset()
	{
		impl->Reset();
	}
}