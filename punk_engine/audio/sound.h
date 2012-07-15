#ifndef _H_PUNK_SOUND
#define _H_PUNK_SOUND

#include <iosfwd>
#include "../system/string.h"

#include "config.h"

namespace Audio
{
	class AudioManager;
	class Player;

	class PUNK_AUDIO_MODULE Sound
	{
		Sound(const Sound&);
		Sound& operator = (const Sound&);
	public:
		Sound();
		~Sound();
		void Init();
		void Clear();
		void Save(std::ostream& stream);
		void Load(std::istream& stream);		

		/// wav, ogg etc.
		//void SetSourceFile(const System::string& file) { m_file = file; }
		//const System::string& GetSourceFile() const { return m_file; }
		//int GetIndex() const { return m_index; }
		//void SetIndex(int value) { m_index = value; }
	private:
		void LoadFromWAV(std::istream& stream);
		unsigned m_buffer;

		friend class AudioManager;
		friend class Player;
	};
}

#endif//	_H_PUNK_SOUND