#include "openal/al_listener_impl.h"

namespace Audio
{
	Listener::Listener()
		: impl(new ListenerImpl)
	{}

	Listener::~Listener()
	{
		delete impl;
		impl = nullptr;
	}

	void Listener::SetGain(float value)
	{
		impl->SetGain(value);
	}

	float Listener::GetGain() const
	{
		return impl->GetGain();
	}

	void Listener::SetPosition(const Math::vec3& value)
	{
		impl->SetPosition(value);
	}

	void Listener::SetPosition(float x, float y, float z)
	{
		impl->SetPosition(Math::vec3(x, y, z));
	}

	const Math::vec3& Listener::GetPosition() const
	{
		return impl->GetPosition();
	}

	void Listener::SetVelocity(const Math::vec3& value)
	{
		impl->SetVelocity(value);
	}

	void Listener::SetVelocity(float x, float y, float z)
	{
		impl->SetVelocity(Math::vec3(x, y, z));
	}

	const Math::vec3& Listener::GetVelocity() const
	{
		return impl->GetVelocity();
	}

	void Listener::SetOrientation(const Math::vec3& at, const Math::vec3& up)
	{
		impl->SetOrientation(at, up);
	}

	const Math::vec3& Listener::GetAtVector() const
	{
		return impl->GetAtVector();
	}

	const Math::vec3& Listener::GetUpVector() const
	{
		return impl->GetUpVector();
	}

	void Listener::Activate()
	{
		impl->Activate();
	}

	void Listener::Deactivate()
	{
		impl->Deactivate();
	}
}