#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE KeyUpEvent : public Event, public Poolable<KeyUpEvent>
    {        
        KeyUpEvent(const KeyUpEvent&);
    public:
		KeyUpEvent();
        int key;	
		virtual string ToString();
    };
}
#endif // KEY_UP_EVENT_H
