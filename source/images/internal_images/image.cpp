#include "image.h"
#include "image_impl.h"

#include <fstream>
#include "../error/module.h"
#include <vector>
#include <algorithm>

namespace ImageModule
{
	Image::Image()
        : impl_image(nullptr)
	{}

    Image::Image(size_t width, size_t height, int channels, ComponentType type, ImageFormat format)
        : impl_image(new ImageImpl(width, height, channels, type, format))
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
		
    void Image::Create(int width, int height, int channels, ComponentType type, ImageFormat format)
	{
        impl_image.reset(new ImageImpl(width, height, channels, type, format));
	}

	unsigned Image::GetSizeInBytes() const
	{
		return impl_image->m_size;
	}

	unsigned Image::GetComponentsCount() const
	{
        return impl_image->m_channels;
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
        auto component_type = GetComponentType();
        auto format = GetImageFormat();
        auto channels = GetComponentsCount();
        impl_image.reset(new ImageImpl(width, height, channels, component_type, format));
	}

	void Image::SetSubImage(unsigned x, unsigned y, const Image& image)
	{
		impl_image->SetSubImage(x, y, *image.impl_image);
	}

    const void* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component) const
	{			
		return impl_image->At(x, y, component);
	}

    void* Image::GetPixelComponent(unsigned x, unsigned y, unsigned component)
	{
		return impl_image->At(x, y, component);
	}

    void Image::SetPixelComponent(unsigned x, unsigned y, unsigned component, const void* value)
	{
        impl_image->Copy(x, y, component, value);
	}

    const void* Image::GetData() const
	{
		return impl_image->At(0,0,0);
	}

    void* Image::GetData()
	{
		return impl_image->At(0,0,0);
	}

	ImageFormat Image::GetImageFormat() const
	{
		return impl_image->m_format;
	}

    void ConvertRGBAtoAlpha(const Image& src, Image& dst)
    {
        for (int y = 0; y != src.GetHeight(); ++y)
        {
            for (int x = 0; x != src.GetWidth(); ++x)
            {
                dst.SetPixelComponent(x, y, 0, src.GetPixelComponent(x, y, 3));
            }
        }
    }

    void ConvertAlphaToRGBA(const Image& src, Image& dst)
    {
        for (int y = 0; y != src.GetHeight(); ++y)
        {
            for (int x = 0; x != src.GetWidth(); ++x)
            {
                const void* c = src.GetPixelComponent(x, y, 0);
                dst.SetPixelComponent(x, y, 0, c);
                dst.SetPixelComponent(x, y, 1, c);
                dst.SetPixelComponent(x, y, 2, c);
                dst.SetPixelComponent(x, y, 3, c);
            }
        }
    }

    const Image Image::ToAlpha() const
    {
        if (GetImageFormat() == IMAGE_FORMAT_ALPHA)
            return *this;
        if (GetImageFormat() == IMAGE_FORMAT_RED)
            return *this;
        if (GetImageFormat() == IMAGE_FORMAT_RGBA)
        {
            Image result(GetWidth(), GetHeight(), 1, GetComponentType(), IMAGE_FORMAT_ALPHA);
            ConvertRGBAtoAlpha(*this, result);
            return result;
        }
    }

    const Image Image::ToRGBA() const
    {
        if (GetImageFormat() == IMAGE_FORMAT_RGBA)
            return *this;
        if (GetImageFormat() == IMAGE_FORMAT_RED || GetImageFormat() == IMAGE_FORMAT_ALPHA)
        {
            Image result(GetWidth(), GetHeight(), 4, GetComponentType(), IMAGE_FORMAT_RGBA);
            ConvertAlphaToRGBA(*this, result);
            return result;
        }
    }

    unsigned Image::GetBitDepth() const
    {
        return impl_image->GetBitDepth();
    }

    ComponentType Image::GetComponentType() const
    {
        return impl_image->m_component_type;
    }
}
