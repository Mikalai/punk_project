#ifdef USE_OPENAL
#define HAS_AUDIO_LISTENER
#include "openal/al_listener_impl.h"
#else
#include "audio_listener.h"
#include "../system/errors/module.h"
#endif // USE_OPENAL

namespace Audio
{
	Listener::Listener()
    #ifdef HAS_AUDIO_LISTENER
		: impl(new ListenerImpl)
	#else
		: impl(nullptr)
	#endif
	{}

	Listener::~Listener()
	{
#ifdef HAS_AUDIO_LISTENER
		delete impl;
		impl = nullptr;
#endif
	}

	void Listener::SetGain(float value)
	{
        (void)value;
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetGain(value);
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	float Listener::GetGain() const
	{
	    #ifdef HAS_AUDIO_LISTENER
		return impl->GetGain();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::SetPosition(const Math::vec3& value)
	{        
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetPosition(value);
        #else
        (void)value;
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::SetPosition(float x, float y, float z)
	{        
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetPosition(Math::vec3(x, y, z));
		#else
        (void)x; (void)y; (void)z;
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	const Math::vec3& Listener::GetPosition() const
	{
	    #ifdef HAS_AUDIO_LISTENER
		return impl->GetPosition();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::SetVelocity(const Math::vec3& value)
	{
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetVelocity(value);
		#else
        (void)value;
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::SetVelocity(float x, float y, float z)
	{
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetVelocity(Math::vec3(x, y, z));
		#else
        (void)x; (void)y; (void)z;
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	const Math::vec3& Listener::GetVelocity() const
	{
	    #ifdef HAS_AUDIO_LISTENER
		return impl->GetVelocity();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::SetOrientation(const Math::vec3& at, const Math::vec3& up)
	{
	    #ifdef HAS_AUDIO_LISTENER
		impl->SetOrientation(at, up);
		#else
        (void)at; (void)up;
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	const Math::vec3& Listener::GetAtVector() const
	{
	    #ifdef HAS_AUDIO_LISTENER
		return impl->GetAtVector();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	const Math::vec3& Listener::GetUpVector() const
	{
	    #ifdef HAS_AUDIO_LISTENER
		return impl->GetUpVector();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::Activate()
	{
	    #ifdef HAS_AUDIO_LISTENER
		impl->Activate();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}

	void Listener::Deactivate()
	{
	    #ifdef HAS_AUDIO_LISTENER
		impl->Deactivate();
		#else
		throw System::PunkException(L"Audio listenere is not available");
		#endif
	}
}
