#include "image.h"
#include "image_impl.h"

#include "../error.h"
#include <vector>
#include <algorithm>

namespace ImageModule
{
	Image::Image()
		: impl_image(new Image::ImageImpl())
	{}

	Image::Image(const Image& image)
		: impl_image(new Image::ImageImpl(*image.impl_image))
	{}

	Image& Image::operator = (const Image& image)
	{
		Image temp(image);
		std::swap(impl_image, temp.impl_image);
		return *this;
	}

	void Image::Save(System::Buffer& buffer) const
	{
		impl_image->Save(buffer);
	}

	void Image::Load(System::Buffer& buffer)
	{
		impl_image->Load(buffer);
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

	void Image::SetSize(unsigned width, unsigned height)
	{
		impl_image->Create(width, height, impl_image->m_components);
	}

	void Image::SetSubImage(unsigned x, unsigned y, const Image& image)
	{
		impl_image->SetSubImage(x, y, *image.impl_image);
	}

	const Image::Component* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component) const
	{			
		return impl_image->At(x, y, component);
	}

	Image::Component* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component)
	{
		return impl_image->At(x, y, component);
	}

	const Image::Component* Image::GetData() const
	{
		return impl_image->At(0,0,0);
	}

	Image::Component* Image::GetData()
	{
		return impl_image->At(0,0,0);
	}
}