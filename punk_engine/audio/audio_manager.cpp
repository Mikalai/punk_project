#include <openal\Framework.h>

#include "audio_manager.h"
#include "../system/logger.h"

namespace System
{
	void Policy<Audio::Sound>::OnInit()
	{
		ALFWInit();

		if (!ALFWInitOpenAL())
		{
			System::Logger::Instance()->WriteError(L"Failed to initialize OpenAL");
			ALFWShutdown();
			return;
		}
	}
		
	void Policy<Audio::Sound>::OnDestroy()
	{
		ALFWShutdownOpenAL();
		ALFWShutdown();
	}
}

//
//	}
//}
//
////
////#include "../system/string.h"
////#include "../system/environment.h"
////#include "../system/config_file.h"
////#include "../system/window.h"
////#include "../system/folder.h"
////
////#include <fstream>
////#include <algorithm>
////#include <iterator>
////#include <string.h>
////
////#include "sound.h"
////#include "audio_manager.h"
////
////namespace Audio
////{
////	std::auto_ptr<AudioManager> AudioManager::m_instance;
////
////	AudioManager* AudioManager::Instance()
////	{
////		if (!m_instance.get())
////		{
////			m_instance.reset(new AudioManager);
////			m_instance->Init();
////		}
////		return m_instance.get();
////	}
////
////	void AudioManager::Destroy()
////	{
////		m_instance.reset(0);
////	}
////
////	AudioManager::AudioManager()
////	{}
////
////	AudioManager::~AudioManager()
////	{
////		Clear();
////	}
////
////	void AudioManager::Init()
////	{
////		ALFWInit();
////
////		if (!ALFWInitOpenAL())
////		{
////			System::Logger::Instance()->WriteError(L"Failed to initialize OpenAL");
////			ALFWShutdown();
////			return;
////		}
////
////		InitPaths();
////
////		UpdateSoundLibrary();
////	}
////
////	void AudioManager::InitPaths()
////	{
////		System::ConfigFile file;
////		file.Open(System::Window::Instance()->GetTitle());
////		if (!file.IsExistOption(L"data"))
////			file.WriteOptionString(L"data", L"d:\\project\\data\\");	
////	/*	if (!file.IsExistOption(L"sounds"))
////			file.WriteOptionString(L"sounds", L"d:\\project\\data\\shaders\\");
////		if (!file.IsExistOption(L"textures"))
////			file.WriteOptionString(L"textures", L"d:\\project\\data\\textures\\");
////		if (!file.IsExistOption(L"data"))
////			file.WriteOptionString(L"data", L"d:\\project\\data\\");	
////		if (!file.IsExistOption(L"fonts"))
////			file.WriteOptionString(L"fonts", L"d:\\project\\data\\font\\");	*/
////		file.Close();
////	}
////
////	void AudioManager::Clear()
////	{
////			ALFWShutdownOpenAL();
////			ALFWShutdown();
////	}
////
////	unsigned AudioManager::LoadFromWAV(const System::string& filename)
////	{	
////		ALuint res = 0;
////		alGenBuffers(1, &res);
////
////		// Load Wave file into OpenAL Buffer
////		char buf[2048];
////		filename.ToANSI(buf, 2048);
////		if (!ALFWLoadWaveToBuffer(buf, res))
////		{
////			System::Logger::Instance()->WriteError(L"Failed to load " + filename);			
////			alDeleteBuffers(1, &res);
////			return 0;
////		}
////
////		return res;
////	}
////
////	Sound* AudioManager::GetSound(int index)
////	{
////		return m_items[index].get();
////	}
////
////	const Sound* AudioManager::GetSound(int index) const
////	{
////		return m_items[index].get();
////	}
////
////	void AudioManager::UpdateSoundLibrary()
////	{
////		System::Folder fld;
////		fld.Open(System::Environment::Instance()->GetSoundFolder());
////		std::list<System::string> files = fld.Find(L"*.snd");		
////		std::list<System::string> temp = fld.Find(L"*.wav");
////		std::list<System::string> cached(temp.begin(), temp.end());		
////		//cached.insert(cached.end(), temp.begin(), temp.end());
////		temp = fld.Find(L"*.ogg");	
////		std::copy(temp.begin(), temp.end(), std::back_inserter(cached));
////		temp = fld.Find(L"*.mp3");	
////		std::copy(temp.begin(), temp.end(), std::back_inserter(cached));
////
////		std::vector<System::string> uncached;
////		for each (System::string file in files)
////		{
////			char buf[2048];
////			file.ToANSI(buf, 2048);
////
////			std::ifstream inp(buf, std::ios_base::binary);
////			Sound snd;
////			snd.Load(inp);
////		
////			auto it = std::find(cached.begin(), cached.end(), snd.m_file);
////			if (it != cached.end())
////			{
////				cached.erase(it);
////			}
////		}
////		
////		for each (System::string file in cached)
////		{
////			if (wcswcs(file.Data(), L".wav") != 0 || wcswcs(file.Data(), L".WAV") != 0)
////			{
////				const wchar_t* pos = wcswcs(file.Data(), L".wav");
////				System::string filename(System::string(file.Data(), (pos - file.Data())) + L".snd");
////				std::auto_ptr<Sound> snd(new Sound);
////				snd->m_file = file;
////				Sound* new_sound = GetSound(ManageSound(snd.release()));
////				char buf[2048];
////				filename.ToANSI(buf, 2048);
////				std::ofstream out(buf, std::ios_base::binary);
////				new_sound->Save(out);
////			}
////		}
////
////		fld.Close();
////	}
////
////	Sound* AudioManager::LoadSound(const System::string& filename)
////	{
////		std::auto_ptr<Sound> snd(new Sound());
////		char buf[2048];
////		filename.ToANSI(buf, 2048);
////		std::ifstream stream(buf, std::ios_base::binary);
////		if (!stream.is_open())
////			return 0;
////		snd->Load(stream);	
////		
////		//	core is wav file
////		if (wcswcs(snd->m_file.Data(), L".wav") != 0
////			|| wcswcs(snd->m_file.Data(), L".WAV") != 0)
////		{
////			snd->m_buffer = Audio::AudioManager::Instance()->LoadFromWAV(System::Environment::Instance()->GetSoundFolder() + snd->m_file);
////		}
////		stream.close();
////		
////		return GetSound(ManageSound(snd.release()));
////	}
////
////	int AudioManager::ManageSound(Sound* snd)
////	{
////		if (snd->m_index == -1)
////		{
////			m_items.push_back(std::shared_ptr<Sound>(snd));
////			m_items[m_items.size()-1]->m_index = m_items.size()-1;
////			return m_items.size()-1;
////		}
////		else
////		{
////			if (snd->m_index >= m_items.size())
////				m_items.resize(snd->m_index + 1);
////			m_items[snd->m_index].reset(snd);
////			return m_items[snd->m_index]->m_index;
////		}
////	}
////}