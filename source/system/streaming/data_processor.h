#ifndef _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR
#define _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR

#include "../../../config.h"
#include "resource_request.h"

namespace System
{
	class PUNK_ENGINE AbstractDataProcessor
	{
	public:
		virtual ~AbstractDataProcessor() {};
		virtual StreamingStepResult LockDeviceObject() = 0;
		virtual StreamingStepResult UnlockDeviceObject() = 0;
		virtual StreamingStepResult Process(void* data, unsigned size) = 0;
		virtual StreamingStepResult CopyToResource() = 0;
		virtual StreamingStepResult SetResourceError() = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR