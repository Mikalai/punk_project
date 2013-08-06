#ifndef PUNK_SYSTEM_MONITOR
#define PUNK_SYSTEM_MONITOR

#ifdef _WIN32
#include <Windows.h>
#elif defined __gnu_linux__
#include <pthread.h>
#endif

namespace System
{
    class Monitor
    {
    public:
        Monitor();
        ~Monitor();
        void Lock();
        bool TryLock();
        void Unlock();
        void Wait();
        void Pulse();
        void PulseAll();

    private:
#ifdef _WIN32
#elif defined __gnu_linux__
    pthread_cond_t m_condition_variable;
    pthread_mutex_t m_mutex;
#endif

    };
}

#endif  //  PUNK_SYSTEM_MONITOR
