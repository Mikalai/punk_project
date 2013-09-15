#ifndef _H_SYSTEM_HANDLER
#define _H_SYSTEM_HANDLER

#include <functional>
#include "events/event.h"


namespace System
{
    struct Handler
    {
        Handler();
        void* object;
        void* method;
		void* reciever;

        void operator() (Event* params) const;
        bool operator == (const Handler& handler);        
    };

    bool operator < (const Handler& l, const Handler& r);

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

	inline Handler EventHandler(void (*f)(Event*))
    {
        Handler handler;
        handler.object = 0;
		handler.reciever = 0;
        void* methodAdr = &f;
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
