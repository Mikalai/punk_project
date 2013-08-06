#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API KeyDownEvent : public Event, public Poolable<KeyDownEvent>
    {        
        KeyDownEvent(const KeyDownEvent&);
    public:        
		KeyDownEvent();
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool prevState;
		bool transitionState;

		virtual string ToString();
    };
}

#endif // KEY_DOWN_EVENT_H
