#include "monitor.h"

namespace System
{
    Monitor::Monitor()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&m_condition_variable, nullptr);
#endif
    }

    Monitor::~Monitor()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_mutex_destroy(&m_mutex);
#endif
    }

    void Monitor::Lock()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_mutex_lock(&m_mutex);
#endif
    }

    void Monitor::Unlock()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_mutex_unlock(&m_mutex);
#endif
    }

    void Monitor::Wait()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_cond_wait(&m_condition_variable, &m_mutex);
#endif
    }

    void Monitor::Pulse()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_cond_signal(&m_condition_variable);
#endif
    }

    void Monitor::PulseAll()
    {
#ifdef _WIN32
#elif defined __gnu_linux__
        pthread_cond_broadcast(&m_condition_variable);
#endif
    }
}
