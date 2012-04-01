#include "rgb_image.h"
#include "image_impl.h"

namespace ImageModule
{
	RGBImage::RGBImage()
		: Image()
	{
		impl_image->m_components = 3;
		impl_image->m_format = IMAGE_FORMAT_RGB;
	}

	RGBImage::RGBImage(const RGBImage& image)
		: Image(image)
	{}

	RGBImage& RGBImage::operator = (const RGBImage& image)
	{
		Image::operator= (image);
		return *this;
	}
}