#ifndef _H_PUNK_APPLICATION
#define _H_PUNK_APPLICATION

#include "config.h"
#include "event_manager.h"
#include "window.h"
#include "singletone.h"

namespace System
{
	SingletoneInterface(Application, LIB_SYSTEM);

	class LIB_SYSTEM Application : public Singletone(Application)
	{
	public:
		Window* GetWindow();
		EventManager* GetEventManager();
		int Run();
		~Application();
	};
}

#endif