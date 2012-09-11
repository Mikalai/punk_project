#ifndef _H_PUNK_SOUND_PLAYER
#define _H_PUNK_SOUND_PLAYER

#include "../config.h"
#include "resource.h"

namespace Audio
{
	class Sound;

	class PUNK_ENGINE Player
	{
		Player(const Player&);
		Player& operator = (const Player&);	
	public:		
		Player();
		~Player();

		void SetSound(System::HResource snd);
		System::HResource GetSound() { return m_sound; }
				
		void Init();
		void Clear();

		bool IsPlaying();
		void Play(bool loop = false);
		void Pause();		
		void Stop();		

	private:

		System::HResource m_sound;
		unsigned m_source;  
		int m_state;
		bool m_loop;

	};
}

#endif