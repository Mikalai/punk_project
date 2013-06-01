#ifndef _H_PUNK_VIDEO_DRIVER
#define _H_PUNK_VIDEO_DRIVER

#include "../../config.h"
#include "../gpu_config.h"
#include "../../system/window/module.h"
#include "../../system/event_manager.h"
#include "../../images/module.h"

namespace Math { class vec4; }
namespace Utility { class FontBuilder; }

namespace GPU
{
	struct VideoDriverDesc
	{
		Config config;
		System::Window* window;
		System::EventManager* event_manager;
	};

    class Texture2D;
	class Frame;

	struct VideoDriverImpl;

	class PUNK_ENGINE_PUBLIC VideoDriver
	{
	public:

		VideoDriver();
		~VideoDriver();

        Utility::FontBuilder* GetFontBuilder();
        void SetFontBuilder(Utility::FontBuilder* value);
		void SetFullScreen(bool flag);
		bool Start(const VideoDriverDesc& desc);
		void Restart();
		void Shutdown();
		System::Window* GetWindow();
		Frame* BeginFrame();
		void EndFrame(Frame* value);
		void SetViewport(float x, float y, float width, float height);
		void SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer);
		void SetClearColor(const Math::vec4& color);
		void SetClearDepth(float value);
		void Clear(bool color, bool depth, bool stencil);
		void SwapBuffers();
        const Config& GetConfig() const;

        Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps);
        Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps);
        Texture2D* CreateTexture2D(const ImageModule::Image& image, bool use_mipmaps);
        Texture2D* CreateTexture2D(const System::string& path, bool use_mipmaps);
		Texture2D* CreateTexture2D(std::istream& stream, bool use_mip_maps);

		/**
		 * @brief CreateTexture2D
		 * @param image Source for the texture
		 * @param internal_format Type of the texture, that should be used in low level graphics API
		 * @param use_mipmaps Flag indicating if mip maps are required
		 * @return Pointer to the created texture.
		 */
		Texture2D* CreateTexture2D(const ImageModule::Image& image, ImageModule::ImageFormat internal_format, bool use_mipmaps);

		VideoDriverImpl* impl;

	private:
		VideoDriver(const VideoDriver&);
		VideoDriver& operator = (const VideoDriver&);
	};
}

#endif	//	_H_PUNK_VIDEO_DRIVER
