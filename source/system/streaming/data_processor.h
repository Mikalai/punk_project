#ifndef _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR
#define _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR

#include "../../../config.h"

namespace System
{
	class PUNK_ENGINE AbstractDataProcessor
	{
	public:
		virtual ~AbstractDataProcessor() {};
		virtual unsigned LockDeviceObject() = 0;
		virtual unsigned UnlockDeviceObject() = 0;
		virtual unsigned Process(void* data, unsigned size) = 0;
		virtual unsigned CopyToResource() = 0;
		virtual unsigned SetResourceError() = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_PROCESSOR