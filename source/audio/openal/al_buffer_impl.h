#ifndef _H_PUNK_AUDIO_OPENAL_BUFFER
#define _H_PUNK_AUDIO_OPENAL_BUFFER

#include "openal.h"
#include "../audio_buffer.h"

namespace Audio
{
	struct BufferImpl
	{
		ALuint m_buffer;
		bool m_has_data;
		System::string m_description;

		BufferImpl();
		~BufferImpl();
		void Destroy();
		void Create();
		void SetData(Format format, void* data, int size, int frequency);
		int GetFrequency() const;
		int GetBits() const;
		int GetChannels() const;
		int GetSize() const;
		void* GetData() const;
		void SetDescription(const System::string& value);
		const System::string& GetDescription() const; 
		bool IsValid() const;
	};
}

#endif	//	_H_PUNK_AUDIO_OPENAL_BUFFER