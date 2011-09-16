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

	void RenderContext::End()
	{
		m_cur_program->Unbind();
	}

}