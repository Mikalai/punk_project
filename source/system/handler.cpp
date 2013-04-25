#include <functional>
#include "handler.h"
#include "events/event.h"


namespace System
{
Handler::Handler()
    : object(nullptr), method(nullptr)
{}

void Handler::operator() (Event* params)
{
    if (object && method)
    {
        class CallObject {};
        CallObject* o = (CallObject*)object;
        void (CallObject::*m)(Event*);
        volatile void** a = (volatile void**)&m;
        volatile void** b = (volatile void**)&method;

        *a = *b;
        if (reciever)
            params->reciever = reciever;

        asm volatile (
            "push %0;"
            "movl %1, %%ecx;"
            "call %2;"
            :
            : "r" (params), "r" (o), "r" (m)
        );

        //(o->*m)(params);
    }

    if (!object && method)
    {
        void (*f)(Event*);
        void** ff = (void**)&f;
        *ff = (void*)method;
        f(params);
    }
}

bool Handler::operator == (const Handler& handler)
{
    return object == handler.object && method == handler.method;
}

}
