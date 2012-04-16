#ifndef _H_PUNK_OPENGL_DRIVER_WIN32
#define _H_PUNK_OPENGL_DRIVER_WIN32
#ifdef _WIN32

#include <map>
#include "../../../../handle.h"
#include "../config.h"
#include "../error.h"
#include "../../../../string.h"
#include "extensions_win32.h"
#include "../render_context/render_context.h"
#include "../texture_context.h"

namespace System
{
	class Window;
	class Event;
}

class ShaderProgram;

namespace OpenGL
{
	class State;
	class Effect;
	class VertexArrayObject;
	class GLSLProgram;
	class Texture2D;

	class MODULE_OPENGL Driver
	{
	public:
		enum Buffer {COLOR_BUFFER = 1, DEPTH_BUFFER = 2, STENCIL_BUFFER = 4};
	private:
		System::string m_path_to_textures;
		System::Window* m_window;
		int m_width;
		int m_height;
		int m_bits_per_pixel;
		bool m_fullscreen;
		int m_refresh_rate;
		int m_shader_version;
		int m_opengl_version;
		HGLRC m_opengl_context;
		std::map<System::string, GLSLProgram*> m_programs;
		std::map<System::string, Texture2D*> m_textures;
		std::multimap<RenderContext*, std::multimap<TextureContext*, VertexArrayObject*> > m_render_queue;

		System::Descriptor m_quad_desc;
		System::Descriptor m_point_desc;

		RenderContext m_render_context;
		TextureContext m_texture_context;

	private:
		void ReadConfig();
		void InitShaderPrograms();
		void SubscribeForSystemMessages();
		void OnResize(System::Event* e);
		void OnKeyPress(System::Event* e);
		void InitInternalVertexBuffers();
	public:
		
		RenderContext* GetRenderContext();
		TextureContext* GetTextureContext();
		Driver();
		void SetFullScreen(bool flag);
		void Start(System::Window* wnd);
		void Restart();
		void Shutdown();
		void SwapBuffers();
		void ClearBuffer(int mask);
		void SetClearColor(float r, float g, float b, float a);
		void* GetProcAddress(const char* name);
		System::Window* GetWindow();
		void SetRenderState(const State* state);
		void SetRenderEffect(const Effect* effect);
		void SetViewport(float x, float y, float width, float height);
		void Render(VertexArrayObject* object);
		void RenderQuad();
		void RenderString(const System::string& s);
		void Render(System::Descriptor desc);
		::ShaderProgram* GetShaderProgram(const System::string& name);
		Texture2D* GetTexture2D(const System::string& texture);

		System::Descriptor CreateStringTexture(const System::string& init_value, int width, int height, int font_size, const System::string& font_name);
		void AlterateStringTexture(System::Descriptor desc, const System::string& value, int width, int height, int font_size, const System::string& font_name);

	};
}

#endif
#endif