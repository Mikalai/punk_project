#ifndef _H_PUNK_IMAGE_MANAGER
#define _H_PUNK_IMAGE_MANAGER

#include <vector>
#include <memory>
#include <iostream>

#include "config.h"
#include "internal_images\image.h"

#include "../system/resource_manager_2.h"
#include "../system/environment.h"

namespace System { class string; }


namespace System
{
	template<> class MODULE_IMAGE Policy<ImageModule::Image>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.png"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetTextureFolder(); }	
		static void OnInit() {}
		static void OnDestroy() {}
	};
}

namespace ImageModule
{		

	class MODULE_IMAGE ImageManager : public System::ResourceManager2<Image, System::Policy>
	{
		ImageManager(const ImageManager&);
		ImageManager& operator = (const ImageManager&);		
	};
}

#endif