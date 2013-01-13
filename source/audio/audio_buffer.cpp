#include "audio_buffer.h"
#include <vector>
#include <ostream>
#include <istream>
#include <openal/al.h>

#include "../system/environment.h"

IMPLEMENT_MANAGER(L"resource.wav_sounds", L"*.wav_sound", System::Environment::Instance()->GetSoundFolder(), System::ObjectType::AUDIO_WAV, Audio, AudioBuffer);

namespace Audio
{
	void OnInit()
	{
		//ALFWInit();

		//if (!ALFWInitOpenAL())
		//{
		//	out_error() << L"Failed to initialize OpenAL" << std::endl;
		//	ALFWShutdown();
		//	return;
		//}
	}

	void OnDestroy()
	{
		//ALFWShutdownOpenAL();
		//ALFWShutdown();
	}

	AudioBuffer::AudioBuffer()
		: m_buffer(0)
//		, m_index(-1)
	{}

	AudioBuffer::~AudioBuffer()
	{
		Clear();
	}

	void AudioBuffer::Clear()
	{
		if (m_buffer != 0)
		{
			alDeleteBuffers(1, &m_buffer);
//			CHECK_ALERROR("alGenBuffers(1, &m_buffer); failed");
			m_buffer = 0;
		}
	}

	void AudioBuffer::Init()
	{
		Clear();
		alGenBuffers(1, &m_buffer);
//		CHECK_ALERROR("alGenBuffers(1, &m_buffer); failed");
	}

	bool AudioBuffer::Save(std::ostream& stream) const
	{				
		//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));		
		//m_file.Save(stream);
		return false;
	}

	bool AudioBuffer::Load(std::istream& stream)
	{
		{			
			// check if this is a wave file
			struct WaveHeader { char riff[4]; int data; char wave[4]; };
			WaveHeader buffer;
			stream.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
			if (memcmp(buffer.riff, "RIFF", 4) == 0 && memcmp(buffer.wave, "WAVE", 4) == 0)
			{			
				stream.seekg(0, std::ios_base::beg);
				LoadFromWAV(stream);
				return true;
			}			
		}					
		return false;
	}

	bool AudioBuffer::LoadFromWAV(std::istream& stream)
	{			
		alGenBuffers(1, &m_buffer);

		//if (!ALFWLoadWaveToBuffer(stream, m_buffer))
		//{
		//	out_error() << L"Failed to load AudioBuffer file from stream" << std::endl;			
		//	alDeleteBuffers(1, &m_buffer);
		//	return false;
		//}
		return false;
	}

	AudioBuffer* AudioBuffer::CreateFromFile(const System::string& path)
	{
		std::unique_ptr<AudioBuffer> buffer(new AudioBuffer);

		std::ifstream stream(path.Data(), std::ios_base::binary);
		if (!buffer->LoadFromWAV(stream))
			return (out_error() << "Can't create audio buffer from file" << std::endl, nullptr);		
		return buffer.release();
	}

	AudioBuffer* AudioBuffer::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<AudioBuffer> buffer(new AudioBuffer);
		buffer->Load(stream);
		return buffer.release();
	}
}
