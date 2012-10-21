#include "../../punk_engine.h"
#include "../../system/system.h"

int main()
{
	System::Window::Instance()->SetTitle(L"PunkAudio Test");
	System::Mouse::Instance()->LockInWindow(false);	
	//	Audio::AudioManager::Instance()->LoadResources();

	auto snd = reinterpret_cast<Audio::AudioBuffer*>(Audio::AudioManager::Instance()->Load(L"m16a2.wav"));

	Audio::Player player;
	player.SetSound(snd);

	player.Play(true);
	//Sleep(1000);
	//player.Stop();

	System::Window::Instance()->Loop();

	player.Stop();

	System::MegaDestroyer::Destroy();
	return 0;
}