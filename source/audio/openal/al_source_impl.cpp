#ifdef USE_OPENAL

#include "al_source_impl.h"

namespace Audio
{
	SourceImpl::SourceImpl()
		: m_source(0)
	{
		alGenSources(1, &m_source);
		ValidateOpenAL(L"Can't create audio source");
	}

	SourceImpl::~SourceImpl()
	{
		if (alIsSource(m_source))
			alDeleteSources(1, &m_source);
	}

	void SourceImpl::SetPitch(float value)
	{
		alSourcef(m_source, AL_PITCH, value);
		ValidateOpenAL(L"Can't set source pitch");
	}

	float SourceImpl::GetPitch() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_PITCH, &value);
		ValidateOpenAL(L"Can't get source pitch");
		return static_cast<float>(value);
	}

	void SourceImpl::SetGain(float value)
	{
		alSourcef(m_source, AL_GAIN, value);
		ValidateOpenAL(L"Can't set source gain");
	}

	float SourceImpl::GetGain() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_GAIN, &value);
		ValidateOpenAL(L"Can't get source gain");
		return static_cast<float>(value);
	}

	void SourceImpl::SetMinGain(float value)
	{
		alSourcef(m_source, AL_MIN_GAIN, value);
		ValidateOpenAL(L"Can't set source min gain");
	}

	float SourceImpl::GetMinGain() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MIN_GAIN, &value);
		ValidateOpenAL(L"Can't get source min gain");
		return static_cast<float>(value);
	}

	void SourceImpl::SetMaxGain(float value)
	{
		alSourcef(m_source, AL_MAX_GAIN, value);
		ValidateOpenAL(L"Can't set source max gain");
	}

	float SourceImpl::GetMaxGain() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source max gain");
		return static_cast<float>(value);
	}

	void SourceImpl::SetRolloffFactor(float value)
	{
		alSourcef(m_source, AL_ROLLOFF_FACTOR, value);
		ValidateOpenAL(L"Can't set source rolloff factor");
	}


	float SourceImpl::GetRolloffFactor() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source rolloff factor");
		return static_cast<float>(value);
	}

	void SourceImpl::SetMaxDistance(float value)
	{
		alSourcef(m_source, AL_MAX_DISTANCE, value);
		ValidateOpenAL(L"Can't set source max distance");
	}

	float SourceImpl::GetMaxDistance() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source max distance");
		return static_cast<float>(value);
	}

	void SourceImpl::SetConeOuterGain(float value)
	{
		alSourcef(m_source, AL_CONE_OUTER_GAIN, value);
		ValidateOpenAL(L"Can't set source cone outer gain");
	}

	float SourceImpl::GetConeOuterGain() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source cone outer gain");
		return static_cast<float>(value);
	}

	void SourceImpl::SetConeInnerAngle(float value)
	{
		alSourcef(m_source, AL_CONE_INNER_ANGLE, value);
		ValidateOpenAL(L"Can't set source cone inner angle");
	}

	float SourceImpl::GetConeInnerAngle() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source cone inner angle");
		return static_cast<float>(value);
	}

	void SourceImpl::SetConeOuterAngle(float value)
	{
		alSourcef(m_source, AL_CONE_OUTER_ANGLE, value);
		ValidateOpenAL(L"Can't set source cone outer angle");
	}

	float SourceImpl::GetConeOuterAngle() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source cone outer angle");
		return static_cast<float>(value);
	}

	void SourceImpl::SetReferenceDistance(float value)
	{
		alSourcef(m_source, AL_REFERENCE_DISTANCE, value);
		ValidateOpenAL(L"Can't set source reference distance");
	}

	float SourceImpl::GetReferenceDistance() const
	{
		ALfloat value;
		alGetSourcef(m_source, AL_MAX_GAIN, &value);
		ValidateOpenAL(L"Can't get source reference distance");
		return static_cast<float>(value);
	}

	void SourceImpl::SetPosition(const Math::vec3& value)
	{
		ALfloat v0 = static_cast<ALfloat>(value[0]);
		ALfloat v1 = static_cast<ALfloat>(value[1]);
		ALfloat v2 = static_cast<ALfloat>(value[2]);
		alSource3f(m_source, AL_POSITION, v0, v1, v2);
		ValidateOpenAL(L"Can't set source position");
	}

	const Math::vec3 SourceImpl::GetPosition() const
	{
		ALfloat v1, v2, v3;
		alGetSource3f(m_source, AL_POSITION, &v1, &v2, &v3);
		ValidateOpenAL(L"Can't get source position");
		Math::vec3 res(static_cast<float>(v1), static_cast<float>(v2), static_cast<float>(v3));
		return res;
	}

	void SourceImpl::SetVelocity(const Math::vec3& value)
	{
		ALfloat v0 = static_cast<ALfloat>(value[0]);
		ALfloat v1 = static_cast<ALfloat>(value[1]);
		ALfloat v2 = static_cast<ALfloat>(value[2]);
		alSource3f(m_source, AL_VELOCITY, v0, v1, v2);
		ValidateOpenAL(L"Can't set source velocity");
	}

	const Math::vec3 SourceImpl::GetVelocity() const
	{
		ALfloat v1, v2, v3;
		alGetSource3f(m_source, AL_VELOCITY, &v1, &v2, &v3);
		ValidateOpenAL(L"Can't get source velocity");
		Math::vec3 res(static_cast<float>(v1), static_cast<float>(v2), static_cast<float>(v3));
		return res;
	}

	void SourceImpl::SetDirection(const Math::vec3& value)
	{
		ALfloat v0 = static_cast<ALfloat>(value[0]);
		ALfloat v1 = static_cast<ALfloat>(value[1]);
		ALfloat v2 = static_cast<ALfloat>(value[2]);
		alSource3f(m_source, AL_DIRECTION, v0, v1, v2);
		ValidateOpenAL(L"Can't set source direction");
	}

	const Math::vec3 SourceImpl::GetDirection() const
	{
		ALfloat v1, v2, v3;
		alGetSource3f(m_source, AL_DIRECTION, &v1, &v2, &v3);
		ValidateOpenAL(L"Can't get source direction");
		Math::vec3 res(static_cast<float>(v1), static_cast<float>(v2), static_cast<float>(v3));
		return res;

	}

	void SourceImpl::SetRelative(bool value)
	{
		alSourcei(m_source, AL_SOURCE_RELATIVE, (value ? AL_TRUE : AL_FALSE));
		ValidateOpenAL(L"Can't bind source to listenenr");
	}

	bool SourceImpl::IsRelative() const
	{
		ALint value;
		alGetSourcei(m_source, AL_SOURCE_RELATIVE, &value);
		ValidateOpenAL(L"Can't get bound state of the source to listener");
		return (value == AL_TRUE ? true : false);
	}

	void SourceImpl::SetLooping(bool value)
	{
		alSourcei(m_source, AL_LOOPING, (value ? AL_TRUE : AL_FALSE));
		ValidateOpenAL(L"Can't set looping state of the source");
	}

	bool SourceImpl::IsLooping() const
	{
		ALint value;
		alGetSourcei(m_source, AL_LOOPING, &value);
		ValidateOpenAL(L"Can't get looping state of the source");
		return (value == AL_TRUE ? true : false);
	}

	void SourceImpl::SetBuffer(Buffer* value)
	{
		alSourcei(m_source, AL_BUFFER, value->impl->m_buffer);
		ValidateOpenAL(L"Can't set source buffer");
	}

	void SourceImpl::Play()
	{
		alSourcePlay(m_source);
		ValidateOpenAL(L"Can't play source");
	}

	bool SourceImpl::IsPlaying() const
	{
		ALint value;
		alGetSourcei(m_source, AL_SOURCE_STATE, &value);
		ValidateOpenAL(L"Can't check source playing state");
		return (value == AL_PLAYING);
	}

	void SourceImpl::Pause()
	{
		alSourcePause(m_source);
		ValidateOpenAL(L"Can't pause source");
	}

	bool SourceImpl::IsPaused() const
	{
		ALint value;
		alGetSourcei(m_source, AL_SOURCE_STATE, &value);
		ValidateOpenAL(L"Can't check source pause state");
		return (value == AL_PAUSED);
	}

	void SourceImpl::Stop()
	{
		alSourcePause(m_source);
		ValidateOpenAL(L"Can't pause source");
	}

	bool SourceImpl::IsStopped() const
	{
		ALint value;
		alGetSourcei(m_source, AL_SOURCE_STATE, &value);
		ValidateOpenAL(L"Can't check source stopped state");
		return (value == AL_STOPPED);
	}

	bool SourceImpl::IsActive() const
	{
		return IsPlaying() || IsPaused();
	}

	void SourceImpl::Reset()
	{
		alSourceRewind(m_source);
		ValidateOpenAL(L"Can't rewind source");
	}

	void SourceImpl::EnqueBuffer(Buffer* value)
	{
		alSourceQueueBuffers(m_source, 1, &value->impl->m_buffer);
		ValidateOpenAL(L"Can't queue buffer in the source");
	}
}

#endif // USE_OPENAL
