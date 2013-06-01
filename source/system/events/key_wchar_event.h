#ifndef KEY_WCHAR_EVENT_H
#define KEY_WCHAR_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC KeyWCharEvent : public Event, public Poolable<KeyWCharEvent>
    {        
        KeyWCharEvent(const KeyWCharEvent&);
    public:
		KeyWCharEvent();

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
