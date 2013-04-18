#include "gl_render_target.h"
#include "../error/module.h"
#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		void OpenGLRenderTarget::ClearTarget()
		{
			GLbitfield b = 0;

			if (m_clear_mask & COLOR_BUFFER)
				b |= GL_COLOR_BUFFER_BIT;
			if (m_clear_mask & DEPTH_BUFFER)
				b |= GL_DEPTH_BUFFER_BIT;
			if (m_clear_mask & STENCIL_BUFFER)
				b |= GL_STENCIL_BUFFER_BIT;

			glClearColor(m_r, m_g, m_b, m_a);
			ValidateOpenGL(L"Unable to set clear color");
			glClear(b);
			ValidateOpenGL(L"Unable to clear buffer");			
		}

		void OpenGLRenderTarget::SetViewport(const Math::Rect& value)
		{
			Activate();
			glViewport((GLsizei)value.GetX(), (GLsizei)value.GetY(), (GLsizei)value.GetWidth(), (GLsizei)value.GetHeight());
			Deactivate();
		}

		bool OpenGLRenderTarget::Init(OpenGLRenderTarget::Properties* props)
		{
			return true;
		}

		void OpenGLRenderTarget::Activate()
		{
		}

		void OpenGLRenderTarget::Deactivate()
		{
		}

		OpenGLRenderTarget::~OpenGLRenderTarget()
		{

		}

	}

}