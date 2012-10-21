#include "player.h"
#include "audio_buffer.h"

#include <openal\Framework.h>

namespace Audio
{
	Player::Player()
		: m_source(0)
		, m_state(0)
		, m_loop(false)
		, m_sound(0)
	{
		Init();
	}

	Player::~Player()
	{
		Clear();
	}

	void Player::Init()
	{
		Clear();
		alGenSources(1, &m_source);
		CHECK_ALERROR("alGenSources(1, &m_source); failed");
		//m_source = 0;
	}	

	void Player::Clear()
	{
		// Clean up by deleting Source(s) and Buffer(s)
		if (m_source != 0)
		{
			alSourceStop(m_source);
			CHECK_ALERROR("alSourceStop(m_source); failed");
			alDeleteSources(1, &m_source);
			CHECK_ALERROR("alDeleteSources(1, &m_source); failed");
		}
	}

	void Player::SetSound(AudioBuffer* snd)
	{
		m_sound = snd; 
		//if (m_sound.GetIndex() != AudioManager::RESOURCE_TYPE)
		//{
		//	out_error() << "Resource handle is not valid" << std::endl;
		//	return;
		//}

		//AudioBuffer* buffer = static_cast<AudioBuffer*>(*m_sound);
		
		// Attach Source to Buffer
		alSourcei(m_source, AL_BUFFER, m_sound->m_buffer);
		CHECK_ALERROR("alSourcei(m_source, AL_BUFFER, m_sound->m_buffer); failed");
	}

	bool Player::IsPlaying()
	{
		alGetSourcei(m_source, AL_SOURCE_STATE, &m_state);
		CHECK_ALERROR("alGetSourcei(m_source, AL_SOURCE_STATE, &m_state); failed");
		return m_state == AL_PLAYING;
	}

	void Player::Play(bool loop)
	{
		if (loop != m_loop)
		{
			m_loop = loop;
			if (m_loop)
			{
				alSourcei(m_source, AL_LOOPING, AL_TRUE);
				CHECK_ALERROR("alSourcei(m_source, AL_LOOPING, AL_TRUE); failed");
			}
			else
			{
				alSourcei(m_source, AL_LOOPING, AL_FALSE);
				CHECK_ALERROR("alSourcei(m_source, AL_LOOPING, AL_FALSE); failed");
			}
		}
		alSourcePlay(m_source);
		CHECK_ALERROR("alSourcePlay(m_source); failed");
	}

	void Player::Stop()
	{
		alSourceStop(m_source);
		CHECK_ALERROR("alSourceStop(m_source); failed");
	}

	void Player::Pause()
	{
		alSourcePause(m_source);
		CHECK_ALERROR("alSourcePause(m_source); failed");
	}
}