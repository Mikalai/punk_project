#ifndef _H_SYSTEM_WIN32_TYPES
#define _H_SYSTEM_WIN32_TYPES

#include "../events/events.h"

typedef signed char Int8;
typedef unsigned char UInt8;
typedef signed short int Int16;
typedef unsigned short int UInt16;
typedef signed int Int32;
typedef unsigned int UInt32;
typedef signed __int64 Int64;
typedef unsigned __int64 UInt64;

namespace System
{
    struct Handler
    {
        Handler() : object(0), method(0) {}
        void* object;
        void* method;
		void* reciever;

        void operator() (Event* params)
        {
            if (object && method)
            {
                class CallObject {};
                CallObject* o = (CallObject*)object;
                void (CallObject::*m)(Event*);
                void** a = (void**)&m;
                void** b = (void**)&method;
                *a = *b;
				if (reciever)
					params->reciever = reciever;
                (o->*m)(params);
            }
        }

        bool operator == (const Handler& handler)
        {
            return object == handler.object && method == handler.method;
        }
    };

    template<class T> Handler EventHandler(T* object, void (T::*method)(Event*))
    {
        Handler handler;
        handler.object = (void*)object;
		handler.reciever = 0;
        void* methodAdr = &method;
        void** a = (void**)methodAdr;
        void** b = (void**)&handler.method;
        *b = *a;
        return handler;
    }

	template<class U, class T> Handler EventHandler(U* reciever, T* object, void (T::*method)(Event*))
    {
        Handler handler;
        handler.object = (void*)object;
		handler.reciever = (void*)reciever;
        void* methodAdr = &method;
        void** a = (void**)methodAdr;
        void** b = (void**)&handler.method;
        *b = *a;
        return handler;
    }
}

#endif //	_H_SYSTEM_TYPES
