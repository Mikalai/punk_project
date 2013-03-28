#include <vector>
#include <ostream>
#include <istream>
#include <fstream>
#include "openal/al_buffer_impl.h"
#include "../system/environment.h"

namespace Audio
{
	Buffer::Buffer()
		: impl(new BufferImpl)
	{}

	Buffer::~Buffer()
	{
		delete impl;
		impl = nullptr;
	}

	void Buffer::SetData(Format format, void* data, int size, int frequency)
	{
		impl->SetData(format, data, size, frequency);
	}

	int Buffer::GetFrequency() const 
	{
		return impl->GetFrequency();
	}

	int Buffer::GetBits() const
	{
		return impl->GetBits();
	}

	int Buffer::GetChannels() const
	{
		return impl->GetChannels();
	}

	int Buffer::GetSize() const
	{
		return impl->GetSize();
	}

	void* Buffer::GetData() const 
	{
		return impl->GetData();
	}

	void Buffer::SetDescription(const System::string& value)
	{
		impl->SetDescription(value);
	}

	const System::string& Buffer::GetDescription() const
	{
		return impl->GetDescription();
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
