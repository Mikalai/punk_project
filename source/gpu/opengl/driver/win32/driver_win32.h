#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32
#ifdef _WIN32

#include <map>
#include <list>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "../../../gpu_config.h"
#include "../../../../config.h"
#include "../../../../system/smart_pointers/module.h"

namespace System
{
	class EventManager;
	class Window;
	class Event;
}

//class ShaderProgram;

namespace GPU
{
	namespace OpenGL
	{
		class Frame;

		struct DriverDesc
		{
			Config config;
			System::Proxy<System::Window> window;
			System::Proxy<System::EventManager> event_manager;
		};

		class PUNK_ENGINE Driver
		{
		public:

			Driver();
			~Driver();

			void SetFullScreen(bool flag);
			bool Start(const DriverDesc& desc);
			void Restart();
			void Shutdown();
			void SwapBuffers();
			void* GetProcAddress(const char* name);

			void OnResize(System::Event* e);
			void OnKeyDown(System::Event* e);

			System::Proxy<System::Window> GetWindow() { return m_desc.window; }

		private:
			
			int m_shader_version;
			int m_opengl_version;
			HGLRC m_opengl_context;
			DriverDesc m_desc;

		private:
			void Init();
			void Clear();
			void ReadConfig();
			void InitShaderPrograms();
			void SubscribeForSystemMessages();
			void InitInternalVertexBuffers();
		};
	}
}
#endif	//	_WIN32

#endif	//	_H_PUNK_OPENGL_DRIVER_WIN32