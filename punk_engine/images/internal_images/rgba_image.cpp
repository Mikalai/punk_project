#include "rgba_image.h"
#include "image_impl.h"

namespace ImageModule
{
	RGBAImage::RGBAImage()
		: Image()
	{
		impl_image->m_components = 4;
	}

	RGBAImage::RGBAImage(const RGBAImage& image)
		: Image(image)
	{
	}

	RGBAImage& RGBAImage::operator = (const RGBAImage& image)
	{
		Image::operator = (image);
		return *this;
	}
}