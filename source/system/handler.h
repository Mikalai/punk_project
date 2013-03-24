#ifndef _H_SYSTEM_HANDLER
#define _H_SYSTEM_HANDLER

#include "events/event.h"

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

			if (!object && method)
			{
				void (*f)(Event*);
				void** ff = (void**)&f;
				*ff = (void*)method;
				f(params);
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
