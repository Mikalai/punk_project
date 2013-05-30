#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32

#ifdef _WIN32
#include <map>
#include <list>

#include "video_memory.h"
#include "../../common/video_driver.h"
#include "../render_targets/module.h"

namespace GPU
{
	struct VideoDriverImpl
	{
		//	video driver interface
		void SetFullScreen(bool flag);
		bool Start(const VideoDriverDesc& desc);
		void Restart();
		void Shutdown();				
		System::Window* GetWindow();
		void SetViewport(float x, float y, float width, float height);
		void SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer);
		void SetClearColor(const Math::vec4& color);
		void SetClearDepth(float value);
		void Clear(bool color, bool depth, bool stencil);
        const Config& GetConfig() const;

		//	constructoion part
		VideoDriverImpl(VideoDriver* driver);
		~VideoDriverImpl();	

		//	implementation part
		void SwapBuffers();
		void OnResize(System::Event* e);
		void OnKeyDown(System::Event* e);

        OpenGL::VideoMemory* GetVideoMemory();
        const OpenGL::VideoMemory* GetVideoMemory() const;

	private:

		int m_shader_version;
		int m_opengl_version;
		HGLRC m_opengl_context;
		VideoDriverDesc m_desc;
        VideoDriver* m_driver;
        OpenGL::VideoMemory* m_memory;
		std::unique_ptr<OpenGL::RenderTarget> m_rt;

	private:
		void Init();
		void Clear();
		void ReadConfig();
		void InitShaderPrograms();
		void SubscribeForSystemMessages();
		void InitInternalVertexBuffers();
	};
}

#endif	//	_WIN32
#endif	//	_H_PUNK_OPENGL_DRIVER_WIN32
