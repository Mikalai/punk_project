#ifndef KEY_WCHAR_EVENT_H
#define KEY_WCHAR_EVENT_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE KeyWCharEvent : public Event
    {
        static std::queue<KeyWCharEvent*> eventPool;
        KeyWCharEvent();
        KeyWCharEvent(const KeyWCharEvent&);
    public:
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool isAltPressed;
		bool prevState;
		bool transitionState;

        virtual void Release();
		virtual string ToString();
        static KeyWCharEvent* Raise();
    };
}

#endif // KEY_CHAR_EVENT_H
