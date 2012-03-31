#include "gray_image.h"
#include "image_impl.h"

namespace ImageModule
{
	GrayImage::GrayImage()
		: Image()
	{
		impl_image->m_components = 1;
	}

	GrayImage::GrayImage(const GrayImage& image)
		: Image(image)
	{}

	GrayImage& GrayImage::operator= (const GrayImage& image)
	{
		Image::operator= (image);
		return *this;
	}
}