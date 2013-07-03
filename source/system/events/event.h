#ifndef EVENT_H
#define EVENT_H

//#include "../allocator.h"
#include "event_type.h"
#include <queue>
#include "../../config.h"
#include "../../string/string.h"
#include "../poolable.h"

namespace System
{
	class PUNK_ENGINE_API Event
    {
    public:
        int eventCode;        
		void* anyData;
		void* reciever;
        //virtual void Release() = 0;
        //char tmp[1024*1024];	//	dummy memory allocation to check memory leaks

		virtual ~Event() {}

		virtual string ToString()
		{
            return string("Code: {0}; NO_DESCRIPTION").arg(eventCode);
		}
    };
}

#endif // EVENT_H
