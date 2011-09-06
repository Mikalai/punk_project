#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

#include "event.h"

namespace System
{
    class LIB_SYSTEM KeyUpEvent : public Event
    {
        static std::queue<KeyUpEvent*> eventPool;
        KeyUpEvent();
        KeyUpEvent(const KeyUpEvent&);
    public:
        int key;
	
		virtual string ToString();
        virtual void Release();
        static KeyUpEvent* Raise();
    };
}
#endif // KEY_UP_EVENT_H
