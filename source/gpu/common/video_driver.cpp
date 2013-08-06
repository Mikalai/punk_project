#ifdef USE_OPENGL
#include "../opengl/driver/gl_driver.h"
#endif

#include <memory.h>
#include "frame_buffer/module.h"
#include "texture/module.h"
#include "frame.h"

namespace Gpu
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
        return CreateTexture2D(width, height, internal_format, format, ImageModule::IMAGE_DATA_TYPE_BYTE, data, use_mipmaps);
    }

    Texture2D* VideoDriver::CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps)
    {

        return CreateTexture2D(width, height, internal_format, format, type, data, use_mipmaps);
    }

    Texture2D* VideoDriver::CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
    {
        auto internal_format = GetInternalFormat(format);
        return CreateTexture2D(width, height, internal_format, format, ImageModule::IMAGE_DATA_TYPE_BYTE, data, use_mipmaps);
    }

    Texture2D* VideoDriver::CreateTexture2D(const ImageModule::Image& image, bool use_mipmaps)
    {
        auto internal_format = GetInternalFormat(image.GetImageFormat());
        return CreateTexture2D(image.GetWidth(), image.GetHeight(), image.GetImageFormat(), image.GetData(), use_mipmaps);
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

    Texture2D* VideoDriver::CreateTexture2D(System::Buffer *buffer, bool use_mip_maps)
    {
        ImageModule::Image image;
        image.Load(buffer);
        return CreateTexture2D(image, use_mip_maps);
    }

	Texture2D* VideoDriver::CreateTexture2D(const ImageModule::Image &image, ImageModule::ImageFormat internal_format, bool use_mipmaps)
	{
        auto format = GetInternalFormat(image.GetImageFormat());
        size_t width = image.GetWidth();
        size_t height = image.GetHeight();
        void* data = (void*)image.GetData();
        std::vector<unsigned char> buffer(image.GetSizeInBytes());
        memcpy(&buffer[0], data, image.GetSizeInBytes());
        return CreateTexture2D(width, height, internal_format, format, data, use_mipmaps);
	}

    FrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height)
    {
        auto fb = *GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        return CreateFrameBuffer(&fb);
    }

    FrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format)
    {
        auto fb = *GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        return CreateFrameBuffer(&fb);
    }

    FrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format, int depth_samples)
    {
        FrameBufferConfig fb = *GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        return CreateFrameBuffer(&fb);
    }

    FrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format, int depth_samples, int coverage_samples)
    {
        FrameBufferConfig fb = *GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        fb.CoverageSamples(coverage_samples);
        return CreateFrameBuffer(&fb);
    }

    Frame* VideoDriver::BeginFrame()
    {
        //  TODO: Safer resource managment should be made here
        Frame* frame = new Frame(this);
        return frame;
    }

    void VideoDriver::EndFrame(Frame* value)
    {
        //  TODO: Safer resource managment should be made here
        delete value;
        SwapBuffers();
    }

    VideoDriver::~VideoDriver()
    {}
}
