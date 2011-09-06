/*
	Monitor.h
	Author: Kirill Surkov, Dmitriy Surkov
	Desc: Monitor for synchronization
*/

#ifndef _H_PUNK_LINUX_MONITOR
#define _H_PUNK_LINUX_MONITOR

class Monitor
{
private:

public:
    Monitor()
    {
    }

    ~Monitor()
    {
    }

    void Enter()
    {

    }

    bool TryEnter()
    {
        return true;
    }

    void Exit()
    {
    }

    void Wait()
    {
    }

    void Pulse()
    {
    }

    void PulseAll()
    {
    }
};

#endif	//_H_PUNK_MONITOR
