#ifndef _H_PUNK_AUDIO_LOADER
#define _H_PUNK_AUDIO_LOADER

#include "../system/streaming/data_loader.h"
#include "../system/streaming/data_processor.h"

namespace Audio
{
	class Buffer;

	class PUNK_ENGINE_API Loader : public System::AbstractDataLoader
	{
	public:
		/**
		*	when 0 returns it means an error
		*/
        virtual System::StreamingStepResult Load() = 0;
		
		/**
		*	when 0 returns it means an error
		*/
        virtual System::StreamingStepResult Decompress(void** data, unsigned* size) = 0;

		/**
		*	when 0 returns it means an error
		*/
        virtual System::StreamingStepResult Destroy() = 0;

	};
}

#endif	//	_H_PUNK_AUDIO_READER
