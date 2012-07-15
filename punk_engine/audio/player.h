#ifndef _H_PUNK_SOUND_PLAYER
#define _H_PUNK_SOUND_PLAYER

#include "config.h"

namespace Audio
{
	class Sound;

	class PUNK_AUDIO_MODULE Player
	{
		Player(const Player&);
		Player& operator = (const Player&);	
	public:		
		Player();
		~Player();

		void SetSound(Sound* snd);
		Sound* GetSound() { return m_sound; }
		const Sound* GetSound() const { return m_sound; }
		
		void Init();
		void Clear();

		bool IsPlaying();
		void Play(bool loop = false);
		void Pause();		
		void Stop();		

	private:

		Sound* m_sound;
		unsigned m_source;  
		int m_state;
		bool m_loop;

	};
}

#endif