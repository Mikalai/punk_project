#ifdef USE_OPENAL

#include "al_listener_impl.h"

namespace Audio
{
	ListenerImpl::ListenerImpl()
		: m_gain(1)
		, m_active(false)
		, m_up_vector(0, 1, 0)
	{}

	void ListenerImpl::SetGain(float value)
	{
		m_gain = value;
		if (m_active)
		{
			alListenerf(AL_GAIN, static_cast<ALfloat>(m_gain));
			ValidateOpenAL(L"Can't set listener gain");
		}
	}

	float ListenerImpl::GetGain() const
	{
		return m_gain;
	}

	void ListenerImpl::SetPosition(const Math::vec3& value)
	{
		m_position = value;
		if (m_active)
		{
			ALfloat v0 = static_cast<ALfloat>(value[0]);
			ALfloat v1 = static_cast<ALfloat>(value[1]);
			ALfloat v2 = static_cast<ALfloat>(value[2]);
			alListener3f(AL_POSITION, v0, v1, v2);
			ValidateOpenAL(L"Can't set listener position");
		}
	}

	const Math::vec3& ListenerImpl::GetPosition() const
	{
		return m_position;
	}

	void ListenerImpl::SetVelocity(const Math::vec3& value)
	{
		m_velocity = value;
		if (m_active)
		{
			ALfloat v0 = static_cast<ALfloat>(value[0]);
			ALfloat v1 = static_cast<ALfloat>(value[1]);
			ALfloat v2 = static_cast<ALfloat>(value[2]);
			alListener3f(AL_VELOCITY, v0, v1, v2);
			ValidateOpenAL(L"Can't set listener velocity");
		}
	}

	const Math::vec3& ListenerImpl::GetVelocity() const
	{
		return m_velocity;
	}

	void ListenerImpl::SetOrientation(const Math::vec3& at, const Math::vec3& up)
	{
		m_at_vector = at;
		m_up_vector = up;
		if (m_active)
		{
			ALfloat data[6];
			data[0] = static_cast<ALfloat>(at[0]);
			data[1] = static_cast<ALfloat>(at[1]);
			data[2] = static_cast<ALfloat>(at[2]);
			data[3] = static_cast<ALfloat>(up[0]);
			data[4] = static_cast<ALfloat>(up[1]);
			data[5] = static_cast<ALfloat>(up[2]);
			alListenerfv(AL_ORIENTATION, data);
			ValidateOpenAL(L"Can't set listener orientation");
		}
	}

	const Math::vec3& ListenerImpl::GetAtVector() const
	{
		return m_at_vector;
	}

	const Math::vec3& ListenerImpl::GetUpVector() const
	{
		return m_up_vector;
	}

	void ListenerImpl::Activate()
	{
		m_active = true;
		SetGain(m_gain);
		SetPosition(m_position);
		SetVelocity(m_velocity);
		SetOrientation(m_at_vector, m_up_vector);
	}

	void ListenerImpl::Deactivate()
	{
		m_active = false;
	}
}

#endif // USE_OPENAL
