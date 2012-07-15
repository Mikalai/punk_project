#include "image.h"
#include "image_impl.h"

#include <fstream>
#include "../error.h"
#include <vector>
#include <algorithm>

namespace ImageModule
{
	Image::Image()
		: impl_image(new ImageImpl())
	{}

	Image::Image(const Image& image)
		: impl_image(new ImageImpl(*image.impl_image))
	{}

	Image& Image::operator = (const Image& image)
	{
		Image temp(image);
		std::swap(impl_image, temp.impl_image);
		return *this;
	}

	Image::~Image()
	{
		impl_image.reset(0);
	}

	void Image::Save(std::ostream& stream) const
	{
		impl_image->Save(stream);
	}

	void Image::Load(std::istream& stream)
	{
		impl_image->Load(stream);
	}

	const System::Descriptor& Image::GetDescriptor() const
	{
		return impl_image->m_descriptor;
	}

	unsigned Image::GetSizeInBytes() const
	{
		return impl_image->m_size;
	}

	unsigned Image::GetComponentsCount() const
	{
		return impl_image->m_components;
	}

	unsigned Image::GetWidth() const
	{
		return impl_image->m_width;
	}

	unsigned Image::GetHeight() const
	{
		return impl_image->m_height;
	}

	unsigned Image::GetBitDepth() const
	{
		return impl_image->m_bit_depth;
	}

	void Image::SetSize(unsigned width, unsigned height)
	{
		impl_image->Create(width, height, impl_image->m_components);
	}

	void Image::SetSubImage(unsigned x, unsigned y, const Image& image)
	{
		impl_image->SetSubImage(x, y, *image.impl_image);
	}

	const Component* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component) const
	{			
		return impl_image->At(x, y, component);
	}

	Component* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component)
	{
		return impl_image->At(x, y, component);
	}

	const Component* Image::GetData() const
	{
		return impl_image->At(0,0,0);
	}

	Component* Image::GetData()
	{
		return impl_image->At(0,0,0);
	}

	ImageFormat Image::GetImageFormat() const
	{
		return impl_image->m_format;
	}
}