#ifndef _H_PUNK_VIDEO_DRIVER
#define _H_PUNK_VIDEO_DRIVER

#include "../../config.h"
#include "../gpu_config.h"
#include "../../system/window/module.h"
#include "../../system/event_manager.h"
#include "../../images/module.h"

namespace Math { class vec4; }
namespace Utility { class FontBuilder; }

namespace Gpu
{
	struct VideoDriverDesc
	{
		Config config;
        Utility::FontBuilder* font_builder;
		System::Window* window;
		System::EventManager* event_manager;
	};

    class RenderTarget;
    class Texture2D;
    class Texture2DArray;
	class Frame;
    class FrameBufferConfig;
    class FrameBuffer;

    struct VideoDriverCaps;

	class PUNK_ENGINE_API VideoDriver
	{
	public:
        VideoDriver() = default;
        virtual ~VideoDriver();
        virtual Utility::FontBuilder* GetFontBuilder() = 0;
        virtual void SetFullScreen(bool flag) = 0;
        virtual System::Window* GetWindow() = 0;
        virtual Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) = 0;
        virtual Texture2DArray* CreateTexture2DArray(int width, int height, int depth, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) = 0;
        virtual FrameBuffer* CreateFrameBuffer(FrameBufferConfig* config) = 0;
        virtual void SetViewport(float x, float y, float width, float height) = 0;
        virtual void SetClearColor(const Math::vec4& color) = 0;
        virtual void SetClearDepth(float value) = 0;
        virtual void Clear(bool color, bool depth, bool stencil) = 0;
        virtual void SwapBuffers() = 0;
        virtual const Config& GetConfig() const = 0;
        virtual size_t GetFrameBufferConfigCount() const = 0;
        virtual FrameBufferConfig* GetFrameBufferConfig(size_t index) = 0;
        virtual FrameBuffer* CreateFrameBuffer() = 0;
        virtual const VideoDriverCaps& GetCaps() = 0;

        Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps);
        Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps);        
        Texture2D* CreateTexture2D(const ImageModule::Image& image, bool use_mipmaps);
        Texture2D* CreateTexture2D(const System::string& path, bool use_mipmaps);
        Texture2D* CreateTexture2D(System::Buffer* buffer, bool use_mip_maps);        
        Texture2D* CreateTexture2D(const ImageModule::Image &image, ImageModule::ImageFormat internal_format, bool use_mipmaps);
        FrameBuffer* CreateFrameBuffer(int width, int height);
        FrameBuffer* CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_color);
        FrameBuffer* CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_color, int depth_samples);
        FrameBuffer* CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_color, int depth_samples, int coverage_samples);        

        Frame* BeginFrame();
        void EndFrame(Frame* value);

		/**
		 * @brief CreateTexture2D
		 * @param image Source for the texture
		 * @param internal_format Type of the texture, that should be used in low level graphics API
		 * @param use_mipmaps Flag indicating if mip maps are required
		 * @return Pointer to the created texture.
		 */
        //Texture2D* CreateTexture2D(const ImageModule::Image& image, ImageModule::ImageFormat internal_format, bool use_mipmaps);

	private:
        VideoDriver(const VideoDriver&) = delete;
        VideoDriver& operator = (const VideoDriver&) = delete;
	};
}

#endif	//	_H_PUNK_VIDEO_DRIVER
