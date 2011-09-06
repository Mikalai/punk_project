#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"

System::Application* app = System::Application::GetInstance();

class Game
{
	System::Clock clock;
public:
	void Main(System::Event* event)
	{
		System::Window* wnd = app->GetWindow();
		//wnd->DrawLine(0,0,100,100);		
		Math::Noise noise;
		noise.SetPersistance(0.1);
		noise.SetOctavesCount(10);
		float prev = wnd->GetHeight() / 2;
		for (int j = 0; j < 256; j++)
		{
			for (int i = 0; i < 256; i++)
			{
				int n = int(255.0f*fabs(noise.PerlinNoise2D(i/60.0f, j/60.0f))) % 255;
				if (n > 128)
					wnd->DrawPixel(i, j, 0, n, 0);
				else
					wnd->DrawPixel(i, j, 255-n, 255-n, 0);

			}
		}
		printf("Complete at");
		wprintf(L" %s ", clock.ToString().Data());		
	}
};

int main()
{
	System::Logger::GetInstance()->WriteError(L"Hi jack");
	System::ConfigFile config;
	config.Open(L"Game");
	config.WriteOptionInt(L"screen_width", 800);
	config.WriteOptionInt(L"screen_width", 640);
	config.WriteOptionInt(L"screen_height", 600);
	config.WriteOptionInt(L"fullscreen", 0);
	config.WriteOptionInt(L"bps", 32);

	config.WriteOptionString(L"player_name", L"chip");
	int res = config.ReadOptionInt(L"screen_width");
	try
	{
		res = config.ReadOptionInt(L"bla");
	}
	catch (System::FileNotFound&)
	{
		config.WriteOptionInt(L"bla", 2);
	}
	res = config.ReadOptionInt(L"bla");
	System::string name = config.ReadOptionString(L"player_name");
	
	config.Close();
	Game g;
	app->GetEventManager()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&g, &Game::Main));
	return app->Run();	
}
