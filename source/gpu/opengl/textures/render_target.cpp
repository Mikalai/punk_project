#include "render_target.h"
#include "../gl/module.h"
#include "../error/module.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderTarget::Properties::Properties()
			: m_type(RENDER_TARGET_NONE)
			, m_clear_mask(COLOR_BUFFER|DEPTH_BUFFER|STENCIL_BUFFER)
			, m_r(0.8f)
			, m_g(0.8f)
			, m_b(0.8f)
			, m_a(1.0f)
		{}

		void RenderTarget::ClearTarget()
		{
			GLbitfield b = 0;

			if (m_clear_mask & COLOR_BUFFER)
				b |= GL_COLOR_BUFFER_BIT;
			if (m_clear_mask & DEPTH_BUFFER)
				b |= GL_DEPTH_BUFFER_BIT;
			if (m_clear_mask & STENCIL_BUFFER)
				b |= GL_STENCIL_BUFFER_BIT;

			glClearColor(m_r, m_g, m_b, m_a);
			CHECK_GL_ERROR(L"Unable to set clear color");
			glClear(b);
			CHECK_GL_ERROR(L"Unable to clear buffer");			
		}

		void RenderTarget::SetClearColor(float r, float g, float b, float a)
		{
			m_r = r; m_g = g; m_b = b; m_a = a;
		}

		void RenderTarget::SetClearMask(int mask)
		{
			m_clear_mask = mask;
		}

		bool RenderTarget::Init(RenderTarget::Properties* props)
		{
			throw OpenGLNotImplemented();
		}

		void RenderTarget::Activate()
		{
			throw OpenGLNotImplemented();
		}

		void RenderTarget::Deactivate()
		{
			throw OpenGLNotImplemented();
		}

		RenderTarget::~RenderTarget()
		{

		}

		void RenderTarget::SetViewport(float x, float y, float width, float height)
		{
			Activate();
			glViewport((GLsizei)x, (GLsizei)y, (GLsizei)width, (GLsizei)height);
			Deactivate();
		}
	}
}
