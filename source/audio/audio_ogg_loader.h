#ifndef _H_PUNK_AUDIO_OGG_LOADER
#define _H_PUNK_AUDIO_OGG_LOADER

#include "audio_loader.h"

namespace System { class string; }

namespace Audio
{
	struct OggLoaderImpl;
	class Buffer;
	
	class PUNK_ENGINE_PUBLIC OggLoader : public Loader
	{
	public:
		
		/**
		*	Filename should be specified here and destination data buffer
		*/
		OggLoader(Buffer* buffer, const System::string& filename);

		~OggLoader();
		/**
		*	when 0 returns it means an error
		*/
		System::StreamingStepResult Load() override;
		
		/**
		*	when 0 returns it means an error
		*/
		System::StreamingStepResult Decompress(void** data, unsigned* size) override;

		/**
		*	when 0 returns it means an error
		*/
		System::StreamingStepResult Destroy() override { return System::StreamingStepResult::STREAM_OK; }

		OggLoaderImpl* impl;

	private:
		OggLoader(const OggLoader&);
		OggLoader(const OggLoader&&);
		OggLoader& operator = (const OggLoader&);
		OggLoader& operator = (const OggLoader&&);
	};
}

#endif	//	_H_PUNK_AUDIO_OGG_LOADER