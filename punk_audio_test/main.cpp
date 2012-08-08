#include "../punk_engine/audio/punk_audio.h"
#include "../punk_engine/system/system.h"

int main()
{
	System::Window::Instance()->SetTitle(L"PunkAudio Test");
	System::Mouse::Instance()->LockInWindow(false);	
//	Audio::AudioManager::Instance()->LoadResources();

	Audio::Sound* snd = Audio::AudioManager::Instance()->Load(L"m16a2.wav");
	
	if (snd)
	{
		Audio::Player player;
		player.SetSound(snd);

		player.Play(true);
		//Sleep(1000);
		//player.Stop();

		System::Window::Instance()->Loop();

		player.Stop();
	}

	Audio::AudioManager::Destroy();

	return 0;
}