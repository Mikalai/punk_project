#include <functional>
#include "handler.h"
#include "events/event.h"


namespace System
{
    Handler::Handler()
        : object(nullptr), method(nullptr)
    {}

    void Handler::operator() (Event* params) const
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

#ifdef _WIN32 && __GNUC__
//            asm volatile (
//                        "push %0;"
//                        "mov %1, %%ecx;"
//                        "call %2;"
//                        :
//                        : "r" (params), "r" (o), "r" (m)
//                        );
#elif defined __gnu_linux__ && __amd64__
                    asm volatile (
                        "movq %0, %%rsi;"
                        "movq %1, %%rdi;"
                        "movq %2, %%rcx;"
                        "callq *%%rcx;"
                        :
                        : "g" (params), "g" (o), "g" (m)
                        : "%rsi", "%rdi", "%rcx"
                    );
#elif defined __gnu_linux__ && __i386__
//            asm ("mov %0, 0x4(%%esp)\n"\
//            "mov %1, %%eax\n"\
//            "mov %%eax, (%%esp)\n"\
//            "call %2"\
//            : \
//            : "r" (params), "g" (o), "g" (m) );
#endif

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

    bool operator < (const Handler& l, const Handler& r)
    {
        return l.object < r.object;
    }
}
