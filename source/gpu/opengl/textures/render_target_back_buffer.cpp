#include "render_target_back_buffer.h"
#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderTargetBackBuffer::RenderTargetBackBufferProperties::RenderTargetBackBufferProperties()
			: Properties()
		{
			m_type = RENDER_TARGET_BACK_BUFFER;
		}

		bool RenderTargetBackBuffer::Init(RenderTargetBackBuffer::Properties* props)
		{
			if (props->m_type != RENDER_TARGET_BACK_BUFFER)
				throw OpenGLInvalidValueException();
			m_clear_mask = props->m_clear_mask;
			m_r = props->m_r;
			m_g = props->m_g;
			m_b = props->m_b;
			m_a = props->m_a;		
			return true;
		}

		void RenderTargetBackBuffer::Activate()
		{
			//	simply unbind all previous buffers
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClearColor(m_r, m_g, m_b, m_a);
			CHECK_GL_ERROR(L"Can't set clear color");
			ClearTarget();
		}

		void RenderTargetBackBuffer::Deactivate()
		{
			//	simply unbind all previous buffers
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		RenderTargetBackBuffer::~RenderTargetBackBuffer()
		{
		}
	}
}