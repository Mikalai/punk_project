#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE KeyDownEvent : public Event
    {
        static std::queue<KeyDownEvent*> eventPool;
        KeyDownEvent();
        KeyDownEvent(const KeyDownEvent&);
    public:        
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool prevState;
		bool transitionState;

        virtual void Release();
		virtual string ToString();
        static KeyDownEvent* Raise();
    };
}

#endif // KEY_DOWN_EVENT_H
