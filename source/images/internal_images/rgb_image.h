#ifndef _H_PUNK_IMAGE_MODULE_RGB_IMAGE
#define _H_PUNK_IMAGE_MODULE_RGB_IMAGE

#include "../../config.h"
#include "image.h"

namespace ImageModule
{
	class PUNK_ENGINE_PUBLIC RGBImage : public Image
	{
	public:
		RGBImage();
		RGBImage(const RGBImage& image);
		RGBImage& operator = (const RGBImage& image);
	};
}

#endif