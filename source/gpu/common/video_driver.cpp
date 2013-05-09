#ifdef USE_OPENGL
#include "../opengl/driver/gl_driver.h"
#endif

#include "texture2d.h"

namespace GPU
{
    Texture2D* VideoDriver::CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
    {
		std::unique_ptr<Texture2D> result(new Texture2D(width, height, format, data, use_mipmaps, this));
        return result.release();
    }

    Texture2D* VideoDriver::CreateTexture2D(const ImageModule::Image& image, bool use_mipmaps)
    {
        std::unique_ptr<Texture2D> result(new Texture2D(image, use_mipmaps, this));
        return result.release();
    }

    Texture2D* VideoDriver::CreateTexture2D(const System::string& path, bool use_mip_maps)
    {
        ImageModule::Importer importer;
        std::unique_ptr<ImageModule::Image> image(importer.LoadAnyImage(path));

        if (image.get())
        {
            std::unique_ptr<Texture2D> result(new Texture2D(*image, use_mip_maps, this));//(*image));
            return result.release();
        }
        else
            throw System::PunkException(L"Can't create texture from " + path);
    }

    Texture2D* VideoDriver::CreateTexture2D(std::istream& stream, bool use_mip_maps)
    {
        ImageModule::Image image;
        image.Load(stream);
        std::unique_ptr<Texture2D> result(new Texture2D(image, use_mip_maps, this));
        return result.release();
    }
}
