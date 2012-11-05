	#ifndef _H_PUNK_AudioBuffer
#define _H_PUNK_AudioBuffer

#include <iosfwd>
#include "../system/object.h"
#include "../string/string.h"

#include "../config.h"

namespace Audio
{
	class AudioManager;
	class Player;

	class PUNK_ENGINE AudioBuffer : public System::Object
	{		
		AudioBuffer(const AudioBuffer&);
		AudioBuffer& operator = (const AudioBuffer&);
	public:
		
		AudioBuffer();
		~AudioBuffer();
		void Init();
		void Clear();
		
		virtual bool Save(std::ostream& stream);
		virtual bool Load(std::istream& stream);		

		/// wav, ogg etc.
		//void SetSourceFile(const System::string& file) { m_file = file; }
		//const System::string& GetSourceFile() const { return m_file; }
		//int GetIndex() const { return m_index; }
		//void SetIndex(int value) { m_index = value; }

		static AudioBuffer* CreateFromFile(const System::string& path);
		static AudioBuffer* CreateFromStream(std::istream& stream);

	private:
		bool LoadFromWAV(std::istream& stream);
		unsigned m_buffer;

		friend class AudioManager;
		friend class Player;
	};	
}

#endif//	_H_PUNK_AudioBuffer