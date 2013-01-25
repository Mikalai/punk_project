#ifndef _H_PUNK_MONITOR_SCOPE
#define _H_PUNK_MONITOR_SCOPE

#include "monitor.h"

class MonitorScope
{
private:
    Monitor& monitor;

    MonitorScope(const MonitorScope&);
    MonitorScope& operator = (const MonitorScope&);

public:
    MonitorScope(Monitor& m) : monitor(m)
    {
        monitor.Enter();
    }

    ~MonitorScope()
    {
        monitor.Exit();
    }
};

#endif
