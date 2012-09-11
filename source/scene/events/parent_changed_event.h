#ifndef SCENE_PARENT_CHANGED_EVENT_H
#define SCENE_PARENT_CHANGED_EVENT_H

#include "../config.h"
#include "../../system/handle.h"
#include "../../system/events/event.h"

namespace Scene
{
	class LIB_SCENE ParentChangedEvent : public System::Event
    {
        static std::queue<ParentChangedEvent*> eventPool;
        ParentChangedEvent();
        ParentChangedEvent(const ParentChangedEvent&);
    public:
		System::Descriptor old_parent;
		System::Descriptor new_parent;
		System::Descriptor instance;
		virtual void Release();
		virtual System::string ToString();
        static ParentChangedEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
