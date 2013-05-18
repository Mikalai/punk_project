#ifdef USE_OPENGL
#include "../opengl/driver/gl_driver.h"
#endif

#include "texture2d.h"

namespace GPU
{
    ImageModule::ImageFormat GetInternalFormat(ImageModule::ImageFormat format)
    {
        switch(format)
        {
        case ImageModule::IMAGE_FORMAT_ALPHA:
        case ImageModule::IMAGE_FORMAT_R32F:
        case ImageModule::IMAGE_FORMAT_RED:
            return ImageModule::IMAGE_FORMAT_RED;
        case ImageModule::IMAGE_FORMAT_RGB:
            return ImageModule::IMAGE_FORMAT_RGB;
        case ImageModule::IMAGE_FORMAT_RGBA:
            return ImageModule::IMAGE_FORMAT_RGBA;
        default:
            throw System::PunkException(L"Can't find suitable internal format");
        }
    }

    Texture2D* VideoDriver::CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
    {
        std::unique_ptr<Texture2D> result(new Texture2D(width, height, internal_format, format, data, use_mipmaps, this));
        return result.release();
    }

    Texture2D* VideoDriver::CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
    {
        auto internal_format = GetInternalFormat(format);
        return CreateTexture2D(width, height, internal_format, format, data, use_mipmaps);
    }

    Texture2D* VideoDriver::CreateTexture2D(const ImageModule::Image& image, bool use_mipmaps)
    {
        auto internal_format = GetInternalFormat(image.GetImageFormat());
        return CreateTexture2D(image, internal_format, use_mipmaps);
    }

    Texture2D* VideoDriver::CreateTexture2D(const System::string& path, bool use_mip_maps)
    {
        ImageModule::Importer importer;
        std::unique_ptr<ImageModule::Image> image(importer.LoadAnyImage(path));

        if (image.get())
        {
            return CreateTexture2D(*image, use_mip_maps);
        }
        else
            throw System::PunkException(L"Can't create texture from " + path);
    }

    Texture2D* VideoDriver::CreateTexture2D(std::istream& stream, bool use_mip_maps)
    {
        ImageModule::Image image;
        image.Load(stream);
        return CreateTexture2D(image, use_mip_maps);
    }

	Texture2D* VideoDriver::CreateTexture2D(const ImageModule::Image &image, ImageModule::ImageFormat internal_format, bool use_mipmaps)
	{
        auto format = GetInternalFormat(image.GetImageFormat());
        size_t width = image.GetWidth();
        size_t height = image.GetHeight();
        void* data = (void*)image.GetData();
        return CreateTexture2D(width, height, internal_format, format, data, use_mipmaps);
	}
}
