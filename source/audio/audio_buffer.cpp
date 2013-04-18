#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include "../system/environment.h"

#ifdef USE_OPENAL
#define HAS_AUDIO_BUFFER
#include "openal/al_buffer_impl.h"
#else
#include "audio_buffer.h"
#endif  //  USE_OPENAL

namespace Audio
{
	Buffer::Buffer()
#ifdef HAS_AUDIO_BUFFER
		: impl(new BufferImpl)
#else
        : impl(nullptr)
#endif
	{}

	Buffer::~Buffer()
	{
		delete impl;
		impl = nullptr;
	}

	void Buffer::SetData(Format format, void* data, int size, int frequency)
	{
	    #ifdef HAS_AUDIO_BUFFER
		impl->SetData(format, data, size, frequency);
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	int Buffer::GetFrequency() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetFrequency();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	int Buffer::GetBits() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetBits();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	int Buffer::GetChannels() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetChannels();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	int Buffer::GetSize() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetSize();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	void* Buffer::GetData() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetData();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	void Buffer::SetDescription(const System::string& value)
	{
	    #ifdef HAS_AUDIO_BUFFER
		impl->SetDescription(value);
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	const System::string& Buffer::GetDescription() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->GetDescription();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	bool Buffer::IsValid() const
	{
	    #ifdef HAS_AUDIO_BUFFER
		return impl->IsValid();
		#else
		throw System::PunkException(L"Audio buffer not supported");
		#endif
	}

	//bool AudioBuffer::Load(std::istream& stream)
	//{
	//	{
	//		// check if this is a wave file
	//		struct WaveHeader { char riff[4]; int data; char wave[4]; };
	//		WaveHeader buffer;
	//		stream.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
	//		if (memcmp(buffer.riff, "RIFF", 4) == 0 && memcmp(buffer.wave, "WAVE", 4) == 0)
	//		{
	//			stream.seekg(0, std::ios_base::beg);
	//			LoadFromWAV(stream);
	//			return true;
	//		}
	//	}
	//	return false;
	//}

	//bool AudioBuffer::LoadFromWAV(std::istream& stream)
	//{
	//	alGenBuffers(1, &m_buffer);

	//	//if (!ALFWLoadWaveToBuffer(stream, m_buffer))
	//	//{
	//	//	out_error() << L"Failed to load AudioBuffer file from stream" << std::endl;
	//	//	alDeleteBuffers(1, &m_buffer);
	//	//	return false;
	//	//}
	//	return false;
	//}

	/*AudioBuffer* AudioBuffer::CreateFromFile(const System::string& path)
	{
		std::unique_ptr<AudioBuffer> buffer(new AudioBuffer);

		std::ifstream stream(path.Data(), std::ios_base::binary);
		if (!buffer->LoadFromWAV(stream))
			throw System::PunkInvalidArgumentException(L"Can't create audio buffer from file");
		return buffer.release();
	}

	AudioBuffer* AudioBuffer::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<AudioBuffer> buffer(new AudioBuffer);
		buffer->Load(stream);
		return buffer.release();
	}*/
}
