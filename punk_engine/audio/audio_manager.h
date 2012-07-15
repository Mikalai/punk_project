#ifndef _H_PUNK_SOUND_MANAGER
#define _H_PUNK_SOUND_MANAGER

#include <vector>
#include <memory>
#include <iostream>

#include "config.h"
#include "sound.h"

#include "../system/resource_manager_2.h"
#include "../system/environment.h"

namespace System { class string; }
namespace Audio
{		
	class PUNK_AUDIO_MODULE AudioManager;
}

namespace System
{
	template<> class PUNK_AUDIO_MODULE Policy<Audio::Sound>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.wav"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetSoundFolder(); }	
		static void OnInit();
		static void OnDestroy();
	};
}

namespace Audio
{		

	class PUNK_AUDIO_MODULE AudioManager : public System::ResourceManager2<Sound, System::Policy>
	{
		AudioManager(const AudioManager&);
		AudioManager& operator = (const AudioManager&);		
	};

	//class PUNK_AUDIO_MODULE AudioManager
	//{
	//public:
	//	typedef std::vector<std::shared_ptr<Sound>> Collection;
	//private:
	//	static std::auto_ptr<AudioManager> m_instance;
	//	
	//	Collection m_items;
	//	AudioManager(const AudioManager&);
	//	AudioManager& operator = (const AudioManager&);
	//
	//	void InitPaths();

	//	void UpdateSoundLibrary();
	//	
	//	//	index a place where to place an object
	//	unsigned LoadFromWAV(const System::string& filename);
	//public:

	//	AudioManager();
	//	~AudioManager();

	//	void Init();
	//	void Clear();

	//	Sound* GetSound(int index);
	//	const Sound* GetSound(int index) const;
	//	// indexed sound file
	//	Sound* LoadSound(const System::string& filename);
	//	//	add sound to manager
	//	int ManageSound(Sound* snd);

	//	Collection& GetAllSounds() { return m_items; }
	//	const Collection& GetAllSounds() const { return m_items; }

	//	static AudioManager* Instance();
	//	static void Destroy();
	//};
}

#endif	//	_H_PUNK_SOUND_MANAGER