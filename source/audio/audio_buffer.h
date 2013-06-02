#ifndef _H_PUNK_AUDIO_BUFFER
#define _H_PUNK_AUDIO_BUFFER

#include <iosfwd>
#include "../system/object.h"
#include "../string/string.h"
#include "audio_format.h"
#include "../config.h"

namespace Audio
{
	struct BufferImpl;

	class PUNK_ENGINE_API Buffer
	{		
	public:
		
		Buffer();
		~Buffer();
		
		static Buffer* CreateFromFile(const System::string& path);
		static Buffer* CreateFromStream(std::istream& stream);

		void SetData(Format format, void* data, int size, int frequency);
		int GetFrequency() const;
		int GetBits() const;
		int GetChannels() const;
		int GetSize() const;
		void* GetData() const;
		void SetDescription(const System::string& value);
		const System::string& GetDescription() const;
		bool IsValid() const;
		BufferImpl* impl;

	private:
		Buffer(const Buffer&);
		Buffer(const Buffer&&);
		Buffer& operator = (const Buffer&);
		Buffer& operator = (const Buffer&&);
	};	
}

#endif//	_H_PUNK_AudioBuffer