#ifndef MODEL_TIME_STEP_H
#define MODEL_TIME_STEP_H

#include "event.h"

namespace System
{
	class PUNK_ENGINE_API ModelTimeStepEvent : public Event, public Poolable<ModelTimeStepEvent>
    {        
        ModelTimeStepEvent(ModelTimeStepEvent&);
    public:
		ModelTimeStepEvent();
		unsigned elapsed_time_ms;
		virtual string ToString();
    };	
}

#endif // MODEL_TIME_STEP_H
