#include <stdio.h>
#include "../punk_engine/images/images.h"
#include "../punk_engine/system/window.h"
#include "../punk_engine/system/mouse.h"
#include "../punk_engine/system/event_manager.h"

class Test
{
	ImageModule::RGBAImage m_image;
public:
	Test()
	{
		ImageModule::Importer file;
		m_image = file.LoadRGBA(L"d:\\project\\data\\textures\\checker2.png");
	}

	void OnMouseClick(System::Event* event)
	{
		for (int y = 0; y < m_image.GetHeight(); ++y)
			for (int x = 0; x < m_image.GetWidth(); ++x)
			{				
				const ImageModule::Image::Component* p = m_image.GetPixelComponent(x, y, 0);
				System::Window::GetInstance()->DrawPixel(x, y, p[0], p[1], p[2], 0);			
			}
	}
};

int main()
{
	try
	{
		Test test;
		System::Window::GetInstance()->SetTitle(L"Punk image test");
		System::Mouse::GetInstance()->LockInWindow(false);

		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(&test, &Test::OnMouseClick));

		System::Window::GetInstance()->Loop();
		
	
	
		printf("File loaded\n");
//		file.Save(L"E:\\project\\textures\\grass_256x256_yo.png");
	//	printf("File saved\n");
	}
	catch(ImageModule::ImageError& err)
	{
		wprintf(L"Error: %s\n", err.w_what());
	}
	catch(System::SystemError& err)
	{
		wprintf(L"Error: %s\n", err.Message().Data());
	}
	return 0;
}