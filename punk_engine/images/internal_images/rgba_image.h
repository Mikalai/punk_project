#ifndef _H_PUNK_IMAGE_RGBA_IMAGE
#define _H_PUNK_IMAGE_RGBA_IMAGE

#include "../config.h"
#include "image.h"
#include <memory>

namespace ImageModule
{
	class MODULE_IMAGE RGBAImage : public Image
	{
	public:
		RGBAImage();
		RGBAImage(const RGBAImage& image);
		RGBAImage& operator = (const RGBAImage& image);
	};

	std::auto_ptr<RGBAImage> ImportRGBAImage(const System::string& filename);
	void ExportRGBAImage(const RGBAImage& image, const System::string& filename);
}

#endif