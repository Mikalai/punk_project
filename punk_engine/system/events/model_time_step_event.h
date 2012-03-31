#ifndef MODEL_TIME_STEP_H
#define MODEL_TIME_STEP_H

#include "event.h"

namespace System
{

    class MODULE_SYSTEM ModelTimeStepEvent : public Event
    {
        static std::queue<ModelTimeStepEvent*> eventPool;		

        ModelTimeStepEvent();
        ModelTimeStepEvent(ModelTimeStepEvent&);
    public:
		unsigned elapsed_time_ms;
        virtual void Release();
		virtual string ToString();
        static ModelTimeStepEvent* Raise();
    };	
}

#endif // MODEL_TIME_STEP_H
