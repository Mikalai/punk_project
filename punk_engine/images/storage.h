#ifndef _H_PUNK_IMAGE_STORAGE
#define _H_PUNK_IMAGE_STORAGE

#include "../system/system.h"
#include "image_file.h"
#include "png_file.h"

namespace Storage
{
	typedef System::Resource<Image::ImageFile> ImageResource;
	typedef System::ResourceManager<ImageResource, System::RESOURCE_IMAGE> ImageManager;
}

#endif