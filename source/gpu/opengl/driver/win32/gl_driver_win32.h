#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32

#ifdef _WIN32
#include <map>
#include <list>

#include "../../../common/video_driver.h"

namespace GPU
{
	struct VideoDriver::VideoDriverImpl
	{
		//	video driver interface
		void SetFullScreen(bool flag);
		bool Start(const VideoDriverDesc& desc);
		void Restart();
		void Shutdown();				
		System::Window* GetWindow();
		Frame* BeginFrame();
		void EndFrame(Frame* value);

		//	constructoion part
		VideoDriverImpl(VideoDriver* driver);
		~VideoDriverImpl();	

		//	implementation part
		void SwapBuffers();
		void OnResize(System::Event* e);
		void OnKeyDown(System::Event* e);

	private:

		int m_shader_version;
		int m_opengl_version;
		HGLRC m_opengl_context;
		VideoDriverDesc m_desc;
		VideoDriver* m_driver;

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