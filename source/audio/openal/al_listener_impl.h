#ifndef _H_PUNK_AUDIO_OPENAL_LISTENER
#define _H_PUNK_AUDIO_OPENAL_LISTENER

#include "openal.h"
#include "../../math/vec3.h"
#include "../audio_listener.h"

namespace Audio
{
	struct ListenerImpl
	{
		float m_gain;
		bool m_active;
		Math::vec3 m_position;
		Math::vec3 m_velocity;
		Math::vec3 m_at_vector;
		Math::vec3 m_up_vector;

		ListenerImpl();

		void SetGain(float value);
		float GetGain() const;
		void SetPosition(const Math::vec3& value);
		const Math::vec3& GetPosition() const;
		void SetVelocity(const Math::vec3& value);
		const Math::vec3& GetVelocity() const;
		void SetOrientation(const Math::vec3& at, const Math::vec3& up);
		const Math::vec3& GetAtVector() const;
		const Math::vec3& GetUpVector() const;
		void Activate();
		void Deactivate();
	};
}

#endif	//	_H_PUNK_AUDIO_OPENAL_LISTENER