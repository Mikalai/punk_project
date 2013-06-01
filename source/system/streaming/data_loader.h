#ifndef _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER
#define _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER

#include "../../config.h"
#include "resource_request.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC AbstractDataLoader
	{
	public:
		virtual ~AbstractDataLoader() {}
		
		/**
		*	when 0 returns it means an error
		*/
		virtual StreamingStepResult Load() = 0;
		
		/**
		*	when 0 returns it means an error
		*/
		virtual StreamingStepResult Decompress(void** data, unsigned* size) = 0;

		/**
		*	when 0 returns it means an error
		*/
		virtual StreamingStepResult Destroy() = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER