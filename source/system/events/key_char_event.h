#ifndef KEY_CHAR_EVENT_H
#define KEY_CHAR_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API KeyCharEvent : public Event, public Poolable<KeyCharEvent>
    {        
        KeyCharEvent(const KeyCharEvent&);
    public:
		KeyCharEvent();
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool isAltPressed;
		bool prevState;
		bool transitionState;
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
