/*
	Monitor.h
	Author: Kirill Surkov, Dmitriy Surkov
	Desc: Monitor for synchronization
*/

#ifndef _H_PUNK_WIN32_MONITOR
#define _H_PUNK_WIN32_MONITOR

#include "../config.h"
#include <windows.h>

class MODULE_SYSTEM Monitor
{
private:

    CRITICAL_SECTION m_mutex;
    CONDITION_VARIABLE m_condVar;

public:
    Monitor()
    {
        ::InitializeCriticalSectionAndSpinCount(&m_mutex, 4000);
        ::InitializeConditionVariable(&m_condVar);
    }

    ~Monitor()
    {
        ::DeleteCriticalSection(&m_mutex);
    }

    void Enter()
    {
        ::EnterCriticalSection(&m_mutex);
    }

    bool TryEnter()
    {
        return ::TryEnterCriticalSection(&m_mutex) != 0;
    }

    void Exit()
    {
        ::LeaveCriticalSection(&m_mutex);
    }

    void Wait()
    {
        ::SleepConditionVariableCS(&m_condVar, &m_mutex, INFINITE);
    }

    void Pulse()
    {
        ::WakeConditionVariable(&m_condVar);
    }

    void PulseAll()
    {
        ::WakeAllConditionVariable(&m_condVar);
    }
};

#endif	//_H_PUNK_WIN32_MONITOR
