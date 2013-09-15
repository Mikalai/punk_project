#include "model_time_step_event.h"

namespace System
{
	ModelTimeStepEvent::ModelTimeStepEvent()
    {
//		eventCode = EVENT_MODEL_TIME_STEP;
    }

	string ModelTimeStepEvent::ToString()
	{
        return string("Code: {0}; Type: MODEL_TIME_STEP; Step: {1}").arg(eventCode).arg(elapsed_time_ms);
	}
}
