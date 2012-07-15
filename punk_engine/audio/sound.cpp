#include "sound.h"
#include <vector>
#include <ostream>
#include <istream>
#include "audio_manager.h"
#include <openal\Framework.h>

#include "../system/environment.h"

namespace Audio
{
	Sound::Sound()
		: m_buffer(0)
//		, m_index(-1)
	{}

	Sound::~Sound()
	{
		Clear();
	}

	void Sound::Clear()
	{
		if (m_buffer != 0)
		{
			alDeleteBuffers(1, &m_buffer);
			CHECK_ALERROR("alGenBuffers(1, &m_buffer); failed");
			m_buffer = 0;
		}
	}

	void Sound::Init()
	{
		Clear();
		alGenBuffers(1, &m_buffer);
		CHECK_ALERROR("alGenBuffers(1, &m_buffer); failed");
	}

	void Sound::Save(std::ostream& stream)
	{				
		//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));		
		//m_file.Save(stream);
	}

	void Sound::Load(std::istream& stream)
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
			}			
		}					
	}

	void Sound::LoadFromWAV(std::istream& stream)
	{			
		alGenBuffers(1, &m_buffer);

		if (!ALFWLoadWaveToBuffer(stream, m_buffer))
		{
			System::Logger::Instance()->WriteError(L"Failed to load sound file from stream");			
			alDeleteBuffers(1, &m_buffer);
		}
	}
}
