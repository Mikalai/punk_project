#include "model_time_step_event.h"

namespace System
{
    std::queue<ModelTimeStepEvent*> ModelTimeStepEvent::eventPool;

    ModelTimeStepEvent::ModelTimeStepEvent()
    {
		eventCode = EVENT_MODEL_TIME_STEP;
    }

    void ModelTimeStepEvent::Release()
    {
        this->eventPool.push(this);
    }

    ModelTimeStepEvent* ModelTimeStepEvent::Raise()
    {
        if (eventPool.empty())
        {
            ModelTimeStepEvent* event = new ModelTimeStepEvent();
            return event;
        }
        else
        {
            ModelTimeStepEvent* event = eventPool.front();
            eventPool.pop();
            return event;
        }
    }

	string ModelTimeStepEvent::ToString()
	{
		return string::Format(L"Code: %d; Type: MODEL_TIME_STEP; Step: %d", eventCode, elapsed_time_ms);
	}
}
