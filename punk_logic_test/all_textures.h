#ifndef _H_ALL_TEXTURES
#define _H_ALL_TEXTURES

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"
#include "../punk_engine/logic/logic.h"
#include "../punk_engine/render/render.h"

struct AllTextures
{
	std::auto_ptr<OpenGL::Texture2D> m_male_skin;
	std::auto_ptr<OpenGL::Texture2D> m_mini14_skin;
	std::auto_ptr<OpenGL::Texture2D> m_m16a2_skin;

	static std::auto_ptr<AllTextures> m_instance;

	AllTextures()
	{
		ImageModule::Importer importer;
		std::auto_ptr<ImageModule::RGBAImage> rgba_image(importer.LoadRGBA(System::Environment::Instance()->GetTexutreFolder() + L"male_skin.png"));
		m_male_skin.reset(new OpenGL::Texture2D(*rgba_image));

		std::auto_ptr<ImageModule::RGBImage> rgb_image(importer.LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"mini14.png"));
		m_mini14_skin.reset(new OpenGL::Texture2D(*rgb_image));

		rgb_image.reset(0);
		rgb_image.reset(importer.LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"m16a2.png"));
		m_m16a2_skin.reset(new OpenGL::Texture2D(*rgb_image));		
	}

	static AllTextures* Instance() 
	{
		if (!m_instance.get())
			m_instance.reset(new AllTextures);
		return m_instance.get();
	}

	static void Destroy()
	{
		m_instance.reset(0);
	}
};


#endif