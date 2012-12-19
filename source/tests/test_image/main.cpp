#include <stdio.h>
#include "../../punk_engine.h"

class Test
{
	System::Proxy<ImageModule::Image> image;

public:
	Test()
	{
		ImageModule::Importer file;
		image.Reset(file.LoadAnyImage(System::Environment::Instance()->GetTextureFolder() + L"face_diffuse.jpg"));
	}

	void OnMouseClick(System::Event* event)
	{
		for (int y = 0; y < image->GetHeight(); ++y)
			for (int x = 0; x < image->GetWidth(); ++x)
			{				
				const ImageModule::Component* p = image->GetPixelComponent(x, y, 0);
				System::Window::Instance()->DrawPixel(x, y, p[0], p[1], p[2], 255);			
			}

		//for (int y = 0; y < m_image_rgb.GetHeight(); ++y)
		//	for (int x = 0; x < m_image_rgb.GetWidth(); ++x)
		//	{				
		//		const ImageModule::Component* p = m_image_rgb.GetPixelComponent(x, y, 0);
		//		System::Window::Instance()->DrawPixel(x, m_image_rgba.GetHeight() + y, p[0], p[1], p[2], 255);			
		//	}

		//for (int y = 0; y < m_image_gray.GetHeight(); ++y)
		//	for (int x = 0; x < m_image_gray.GetWidth(); ++x)
		//	{				
		//		const ImageModule::Component* p = m_image_gray.GetPixelComponent(x, y, 0);
		//		System::Window::Instance()->DrawPixel(m_image_rgba.GetWidth() + x, y, p[0], p[0], p[0], 255);			
		//	}
	}
};

int main()
{
	try
	{
		Test test;
		System::Window::Instance()->SetTitle(L"Punk image test");
		System::Mouse::Instance()->LockInWindow(false);

		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(&test, &Test::OnMouseClick));

		System::Window::Instance()->Loop();
		
	
	
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