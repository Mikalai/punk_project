#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	class Test
	{		
		Audio::Buffer buffer;
		Audio::Source source;
		unsigned result;
	public:
		Test()
		{
			System::AsyncLoader::Instance()->InitAsyncLoading(4);
			Audio::OggLoader* loader = new Audio::OggLoader(&buffer, System::Environment::Instance()->GetSoundFolder() + L"mini14.ogg");
			Audio::OggProcessor* processor = new Audio::OggProcessor();
			System::AsyncLoader::Instance()->AddWorkItem(loader, processor, &result);
		}

		~Test()
		{
			System::AsyncLoader::Destroy();
		}

		void TryToPlay()
		{	
			while (!source.IsPlaying())
			{
				System::AsyncLoader::Instance()->MainThreadProc(1);
				if (buffer.IsValid())
				{
					source.SetBuffer(&buffer);
					source.Play();
				}				
			}

			while (source.IsPlaying())
			{
				Sleep(1000);
			}
		}
	};

	TEST_CLASS(sound_test)
	{
	public:
		
		TEST_METHOD(SoundTestOggPlay)
		{
			{
				std::unique_ptr<Audio::SoundSystem> s(new Audio::SoundSystem);
				s->Initialize();

				{
					Test test;
					test.TryToPlay();
				}
			}
		}

	};
}