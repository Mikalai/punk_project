#ifndef _H_SYSTEM_LINUX_TYPES
#define _H_SYSTEM_LINUX_TYPES

typedef signed char Int8;
typedef unsigned char UInt8;
typedef signed short int Int16;
typedef unsigned short int UInt16;
typedef signed int Int32;
typedef unsigned int UInt32;
typedef signed long long int Int64;
typedef unsigned long long int UInt64;

#define PUNK_KEY_LEFT_ALT           0x01
#define PUNK_KEY_RIGHT_ALT          0x02
#define PUNK_KEY_TAB                0x03
#define PUNK_KEY_CAPSLOCK           0x04
#define PUNK_KEY_PAGE_UP            0x05
#define PUNK_KEY_PAGE_DOWN          0x06

#define PUNK_KEY_ENTER              0x0D

#define PUNK_KEY_ESCAPE             0x1B
#define PUNK_KEY_SPACE              0x20
#define PUNK_KEY_END                0x23
#define PUNK_KEY_HOME               0x24

#define PUNK_KEY_LEFT               0x25
#define PUNK_KEY_UP                 0x26
#define PUNK_KEY_RIGHT              0x27
#define PUNK_KEY_DOWN               0x28

#define PUNK_KEY_INSERT             0x2D
#define PUNK_KEY_DELETE             0x2E

#define PUNK_KEY_0                  0x30
#define PUNK_KEY_1                  0x31
#define PUNK_KEY_2                  0x32
#define PUNK_KEY_3                  0x33
#define PUNK_KEY_4                  0x34
#define PUNK_KEY_5                  0x35
#define PUNK_KEY_6                  0x36
#define PUNK_KEY_7                  0x37
#define PUNK_KEY_8                  0x38
#define PUNK_KEY_9                  0x39

#define PUNK_KEY_A                  0x41
#define PUNK_KEY_B                  0x42
#define PUNK_KEY_C                  0x43
#define PUNK_KEY_D                  0x44
#define PUNK_KEY_E                  0x45
#define PUNK_KEY_F                  0x46
#define PUNK_KEY_G                  0x47
#define PUNK_KEY_H                  0x48
#define PUNK_KEY_I                  0x49
#define PUNK_KEY_J                  0x4A
#define PUNK_KEY_K                  0x4B
#define PUNK_KEY_L                  0x4C
#define PUNK_KEY_M                  0x4D
#define PUNK_KEY_N                  0x4E
#define PUNK_KEY_O                  0x4F
#define PUNK_KEY_P                  0x50
#define PUNK_KEY_Q                  0x51
#define PUNK_KEY_R                  0x52
#define PUNK_KEY_S                  0x53
#define PUNK_KEY_T                  0x54
#define PUNK_KEY_U                  0x55
#define PUNK_KEY_V                  0x56
#define PUNK_KEY_W                  0x57
#define PUNK_KEY_X                  0x58
#define PUNK_KEY_Y                  0x59
#define PUNK_KEY_Z                  0x5A

#define PUNK_KEY_NUM0               0x60
#define PUNK_KEY_NUM1               0x61
#define PUNK_KEY_NUM2               0x62
#define PUNK_KEY_NUM3               0x63
#define PUNK_KEY_NUM4               0x64
#define PUNK_KEY_NUM5               0x65
#define PUNK_KEY_NUM6               0x66
#define PUNK_KEY_NUM7               0x67
#define PUNK_KEY_NUM8               0x68
#define PUNK_KEY_NUM9               0x69

#define PUNK_KEY_F1                 0x70
#define PUNK_KEY_F2                 0x71
#define PUNK_KEY_F3                 0x72
#define PUNK_KEY_F4                 0x73
#define PUNK_KEY_F5                 0x74
#define PUNK_KEY_F6                 0x75
#define PUNK_KEY_F7                 0x76
#define PUNK_KEY_F8                 0x77
#define PUNK_KEY_F9                 0x78
#define PUNK_KEY_F10                0x79
#define PUNK_KEY_F11                0x7A
#define PUNK_KEY_F12                0x7B

#define PUNK_KEY_LEFT_SHIFT         0xA0
#define PUNK_KEY_RIGHT_SHIFT        0xA1
#define PUNK_KEY_LEFT_CONTROL       0xA2
#define PUNK_KEY_RIGHT_CONTROL      0xA3

namespace System
{
    class Event;

    struct Parameters
    {
    };

    struct Handler
    {
        Handler() : object(0), method(0) {}
        void* object;
        void* method;

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

                asm ("mov %0, 0x4(%%esp)\n"\
                     "mov %1, %%eax\n"\
                     "mov %%eax, (%%esp)\n"\
                     "call %2"\
                      : \
                      : "r" (params), "g" (o), "g" (m) );
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
        void* methodAdr = &method;
        void** a = (void**)methodAdr;
        void** b = (void**)&handler.method;
        *b = *a;
        return handler;
    }
}

#endif // _H_SYSTEM_LINUX_TYPES
