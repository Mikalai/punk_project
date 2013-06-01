#include "model_time_step_event.h"

namespace System
{
	ModelTimeStepEvent::ModelTimeStepEvent()
    {
		eventCode = EVENT_MODEL_TIME_STEP;
    }

	string ModelTimeStepEvent::ToString()
	{
		return string("Code: %d; Type: MODEL_TIME_STEP; Step: %d", eventCode, elapsed_time_ms);
	}
}
