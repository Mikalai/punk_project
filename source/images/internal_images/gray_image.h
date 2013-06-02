#ifndef _H_PUNK_IMAGE_MODULE_GRAY
#define _H_PUNK_IMAGE_MODULE_GRAY

#include "../../config.h"
#include "image.h"

namespace ImageModule
{
	class PUNK_ENGINE_API GrayImage : public Image
	{
	public:
		GrayImage();
		GrayImage(const GrayImage& image);
		GrayImage& operator = (const GrayImage& image);
	};
}

#endif