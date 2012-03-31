#include "render_context.h"
#include "shader_program.h"
#include "win32/driver_win32.h"

namespace OpenGL
{
	void RenderContext::Begin(ShaderProgram* program)
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(1,1,1,1);
		//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		m_cur_program = program;
		m_cur_program->Bind();
	}

	ShaderProgram* RenderContext::GetShaderProgram()
	{
		return m_cur_program;
	}

	void RenderContext::End()
	{
		m_cur_program->Unbind();
	}

	void RenderContext::EnableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderContext::DisableBlending()
	{
		glDisable(GL_BLEND);
	}

	void RenderContext::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void RenderContext::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}
}