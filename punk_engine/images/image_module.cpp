#include "image_module.h"
#include "resources\rgba_image_resource.h"
#include "resources\rgb_image_resource.h"
#include "resources\gray_image_resource.h"

#include "../system/resource_factory.h"

namespace ImageModule
{
	static wchar_t MODULE_NAME[] = L"image_module";

	unsigned short RESOURCE_RGBA_IMAGE;
	unsigned short RESOURCE_RGB_IMAGE;
	unsigned short RESOURCE_GRAY_IMAGE;
	unsigned short RESOURCE_ENVIRONMENT_MAP;
	unsigned short RESOURCE_CUBE_MAP;

	unsigned short RESOURCE_BASE = 0;

	void Module::Init()
	{
		RESOURCE_BASE = System::ResourceFactory::GetBaseTypeCode(MODULE_NAME);		
		unsigned short type_code = RESOURCE_BASE;		
		const unsigned short int base = System::ResourceFactory::GetBaseTypeCode(MODULE_NAME);		
		RESOURCE_RGBA_IMAGE = ++type_code;
		System::ResourceFactory::Instance()->RegisterResource(RESOURCE_RGBA_IMAGE, new RGBAImageResource(System::Descriptor(type_code, 0)));
		RESOURCE_RGB_IMAGE = ++type_code;
		System::ResourceFactory::Instance()->RegisterResource(RESOURCE_RGB_IMAGE, new RGBImageResource(System::Descriptor(type_code, 0)));
		RESOURCE_GRAY_IMAGE = ++type_code;
		System::ResourceFactory::Instance()->RegisterResource(RESOURCE_GRAY_IMAGE, new GrayImageResource(System::Descriptor(type_code, 0)));
	}

	unsigned short Module::RGBA_IMAGE_RESOURCE_TYPE_CODE()
	{
		return RESOURCE_RGBA_IMAGE;
	}

	unsigned short Module::RGB_IMAGE_RESOURCE_TYPE_CODE()
	{
		return RESOURCE_RGB_IMAGE;
	}

	unsigned short Module::GRAY_IMAGE_RESOURCE_TYPE_CODE()
	{
		return RESOURCE_GRAY_IMAGE;
	}
}