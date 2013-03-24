#include "image.h"
#include "image_impl.h"

#include <fstream>
#include "../error/module.h"
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

	bool Image::Save(std::ostream& stream) const
	{
		return impl_image->Save(stream);
	}

	bool Image::Load(std::istream& stream)
	{
		char header[16];
		stream.read(header, 16);
		{
			unsigned char png[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
			if (!memcmp(header, png, 8))
			{					
				stream.seekg(0, std::ios_base::beg);
				PngImporter importer;
				return importer.Load(stream, this);
			}

			unsigned char jpg[] = {0xFF, 0xD8};
			if (!memcmp(header, jpg, 2))
			{
				stream.seekg(0, std::ios_base::beg);
				JpgImporter importer;
				return importer.Load(stream, this);
			}
			return false;
		}
	}
		
	void Image::Create(int width, int height, int channels)
	{
		impl_image->Create(width, height, channels);
	}

	void Image::SetFormat(int format)
	{
		impl_image->SetFormat(format);
	}

	void Image::SetNumChannels(int channels)
	{
		impl_image->SetNumChannels(channels);
	}

	void Image::SetDepth(int bpp)
	{
		impl_image->SetDepth(bpp);
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

	void Image::SetPixelComponent(unsigned x, unsigned y, unsigned component, Component value)
	{
		*impl_image->At(x, y, component) = value;
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