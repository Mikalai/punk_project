#ifndef EVENT_H
#define EVENT_H

//#include "../allocator.h"
#include "event_type.h"
#include <queue>
#include "../config.h"
#include "../string.h"

namespace System
{
	class MODULE_SYSTEM Event
    {
    public:
        int eventCode;        
		void* anyData;
        virtual void Release() = 0;
		virtual string ToString()
		{
			return string::Format(L"Code: %d; NO_DESCRIPTION", eventCode);
		}
    };
}

#endif // EVENT_H
