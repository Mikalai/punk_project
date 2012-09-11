#ifndef KEY_CHAR_EVENT_H
#define KEY_CHAR_EVENT_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE KeyCharEvent : public Event
    {
        static std::queue<KeyCharEvent*> eventPool;
        KeyCharEvent();
        KeyCharEvent(const KeyCharEvent&);
    public:
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool isAltPressed;
		bool prevState;
		bool transitionState;
		virtual string ToString();
        virtual void Release();
        static KeyCharEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
