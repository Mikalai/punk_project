#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32
#ifdef _WIN32

#include <map>
#include <list>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include "../../../../config.h"

namespace System
{
	class Window;
	class Event;
}

//class ShaderProgram;

namespace GPU
{
	namespace OpenGL
	{
		class Frame;

		class PUNK_ENGINE Driver
		{
		private:

			int m_width;
			int m_height;
			int m_bits_per_pixel;
			bool m_fullscreen;
			int m_refresh_rate;
			int m_shader_version;
			int m_opengl_version;
			HGLRC m_opengl_context;

		private:
			void Init();
			void Clear();
			void ReadConfig();
			void InitShaderPrograms();
			void SubscribeForSystemMessages();
			void OnResize(System::Event* e);
			void OnKeyPress(System::Event* e);
			void InitInternalVertexBuffers();

		public:

			Driver();
			~Driver();

			void SetFullScreen(bool flag);
			bool Start();
			void Restart();
			void Shutdown();
			void SwapBuffers();
			void* GetProcAddress(const char* name);

			static Driver* Instance();
			static void Destroy();

		private:
			static Driver* m_instance;
		};
	}
}
#endif	//	_WIN32

#endif	//	_H_PUNK_OPENGL_DRIVER_WIN32