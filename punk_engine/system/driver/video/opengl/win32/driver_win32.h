#ifdef _WIN32

#include <map>
#include "../config.h"
#include "../error.h"
#include "../../../../string.h"
#include "extensions_win32.h"

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
	class TextureContext;
	class RenderContext;

	class LIB_OPENGL Driver
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

		VertexArrayObject* m_quad;

	private:
		void ReadConfig();
		void InitShaderPrograms();
		void SubscribeForSystemMessages();
		void OnResize(System::Event* e);
		void OnKeyPress(System::Event* e);
		void InitInternalVertexBuffers();
	public:
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
		void Render(VertexArrayObject* object);
		void RenderQuad(float x, float y, float with, float height);
		void RenderString(float x, float y, float width, float height, const System::string& s);
		::ShaderProgram* GetShaderProgram(const System::string& name);
		Texture2D* GetTexture2D(const System::string& texture);
	};
}

#endif