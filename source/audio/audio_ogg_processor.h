#ifndef _H_PUNK_AUDIO_OGG_PROCESSOR
#define _H_PUNK_AUDIO_OGG_PROCESSOR

#include "../config.h"
#include "../system/streaming/data_processor.h"

namespace Audio
{
	class Buffer;

	/**
	*	This processor does nothing. Exist only for compatibility with async loading
	*/
	class PUNK_ENGINE_API OggProcessor : public System::AbstractDataProcessor
	{
	public:
		/**
		*	Destroys internal implementation
		*/
		virtual ~OggProcessor() {};
		/**
		*	This do nothing, because we have a texture to copy data in
		*/
		System::StreamingStepResult LockDeviceObject() override { return System::StreamingStepResult::STREAM_OK; };
		/**
		*	This do nothing 
		*/
		System::StreamingStepResult UnlockDeviceObject() override { return System::StreamingStepResult::STREAM_OK; };
		/**
		*	This can perform data convertion, if float textures
		*	are not supported
		*/
        System::StreamingStepResult Process(void*, unsigned) override { return System::StreamingStepResult::STREAM_OK; };
		/**
		*	Data is copied to the texture here
		*/
		System::StreamingStepResult CopyToResource() override { return System::StreamingStepResult::STREAM_OK; };

		System::StreamingStepResult SetResourceError() override { return System::StreamingStepResult::STREAM_OK; };
	};
}
#endif	//	_H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR
