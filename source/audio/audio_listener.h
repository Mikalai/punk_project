#ifndef _H_PUNK_AUDIO_LISTENER
#define _H_PUNK_AUDIO_LISTENER

#include "../config.h"

namespace Math { class vec3; }

namespace Audio
{
	struct ListenerImpl;

	class PUNK_ENGINE_PUBLIC Listener
	{
	public:
		Listener();
		virtual ~Listener();

		void SetGain(float value);
		float GetGain() const;
		void SetPosition(const Math::vec3& value);
		void SetPosition(float x, float y, float z);
		const Math::vec3& GetPosition() const;
		void SetVelocity(const Math::vec3& value);
		void SetVelocity(float x, float y, float z);
		const Math::vec3& GetVelocity() const;
		void SetOrientation(const Math::vec3& at, const Math::vec3& up);
		const Math::vec3& GetAtVector() const;
		const Math::vec3& GetUpVector() const;
		void Activate();
		void Deactivate();

		ListenerImpl* impl;

	private:
		Listener(const Listener&);
		Listener(const Listener&&);
		Listener& operator = (const Listener&);
		Listener& operator = (const Listener&&);
	};
}

#endif	//	_H_PUNK_AUDIO_LISTENER
