#include "gl_render_context.h"
#include "../error/module.h"
#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		OpenGLRenderContext::OpenGLRenderContext()
			: m_program(0)
		{}

		void OpenGLRenderContext::Begin()
		{
			glUseProgram(m_program);
		}

		void OpenGLRenderContext::End()
		{
			glUseProgram(0);
		}

		void OpenGLRenderContext::Init()
		{
			try
			{
				if (m_was_modified || !m_program)
				{
					if (m_program)
					{
						glDeleteProgram(m_program);
						ValidateOpenGL(L"Unable to delete shader program");
					}
					m_program = glCreateProgram();
					ValidateOpenGL(L"Unable to create shader program");
					if (m_vertex_shader.get())
					{
						glAttachShader(m_program, m_vertex_shader->GetIndex());
						ValidateOpenGL(L"Unable to attach vertex shader to shader program");
					}
					else
					{
						out_error() << L"Vertex shader not set" << std::endl;
						return;
					}

					if (m_fragment_shader.get())
					{
						glAttachShader(m_program, m_fragment_shader->GetIndex());
						ValidateOpenGL(L"Unable to attach fragment shader to shader program");
					}
					else
					{
						out_error() << L"Fragment shader not set" << std::endl;
						return;
					}

					if (m_geometry_shader.get())
					{
						glAttachShader(m_program, m_geometry_shader->GetIndex());				
						ValidateOpenGL(L"Unable to attach geometry shader to shader program");
					}

					glLinkProgram(m_program);
					ValidateOpenGL(L"Unable to link shader program");

					GLint status;
					glGetProgramiv(m_program, GL_LINK_STATUS, &status);
					ValidateOpenGL(L"Unable to get link status of the shader program");
					if (status == GL_TRUE)
					{
						glValidateProgram(m_program);
						ValidateOpenGL(L"Unable to validate shader program");
						glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
						ValidateOpenGL(L"Unable to get validation status of the shader program");
						if (status != GL_TRUE)
						{
							out_error() << L"Shader program validation failed" << std::endl;
							return;
						}

					}
					else
					{
						out_error() << L"Unable to link shader program" << std::endl;
						return;
					}
					m_was_modified = false;
				}
			}
			catch(...)
			{
				glDeleteProgram(m_program);
				m_program = 0;
				throw;
			}
		}

		bool OpenGLRenderContext::SetUniformVector4f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform4fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformVector4f( int loc, const float* value )
		{
			glUniform4fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformVector3f(const char * name, const float* value )
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniform3fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformVector3f(int loc, const float* value)
		{
			glUniform3fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformVector2f(const char * name, const float* value )
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniform2fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformVector2f(int loc, const float* value )
		{
			glUniform2fv(loc, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformFloat(const char * name, float value)
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniform1f(loc, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformFloat(int loc, float value)
		{
			glUniform1f ( loc, value );
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(const char * name, int value)
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniform1i ( loc, value );
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(int loc, int value)
		{
			glUniform1i( loc, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix2f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation ( m_program, name );
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniformMatrix2fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix2f( int loc, const float* value)
		{		
			glUniformMatrix2fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix3f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation ( m_program, name );
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix3f( int loc, const float* value)
		{		
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix4f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation ( m_program, name );
			ValidateOpenGL(L"Unable to get uniform location");				
			glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix4f( int loc, const float* value)
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformArrayMatrix4f(int loc, int count, const float* value)
		{
			glUniformMatrix4fv(loc, count, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}


		int OpenGLRenderContext::GetUniformLocation(const char * name)
		{
			GLint res = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			return res;
		}

		void OpenGLRenderContext::GetUniformVector(const char * name, float* out)
		{
			int loc = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");				
			glGetUniformfv(m_program, loc, out);
		}

		bool OpenGLRenderContext::SetTexture(const char * name, int texUnit)
		{
			int loc = glGetUniformLocation ( m_program, name );
			//	if ( loc == -1 )
			//	throw System::SystemError(L"Can't set texture: " + System::string(name));
			glUniform1i(loc, texUnit);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetTexture(int loc, int texUnit)
		{
			//	if ( loc < 0 )
			//	throw System::SystemError(L"Can't set texture");
			glUniform1i(loc, texUnit);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::BindAttributeTo(int loc, const char * name)
		{
			glBindAttribLocation(m_program, loc, name);
			ValidateOpenGL(L"Unable to bind attribute");
			return true;
		}

		bool OpenGLRenderContext::SetAttribute(const char * name, const float* value)
		{
			int index = glGetAttribLocation(m_program, name);
			ValidateOpenGL(L"Unable to get attribute location");
			glVertexAttrib4fv ( index, value );
			ValidateOpenGL(L"Unable to set attribute");
			return true;
		}

		bool OpenGLRenderContext::SetAttribute(int index, const float* value)
		{
			glVertexAttrib4fv(index, value);
			ValidateOpenGL(L"Unable to get attribute value");
			return true;
		}

		int OpenGLRenderContext::IndexForAttrName(const char * name)
		{
			int res = glGetAttribLocation(m_program, name);
			ValidateOpenGL(L"Unable to get attribute index");
			return res;
		}

		void OpenGLRenderContext::GetAttribute(const char * name, float* out)
		{
			int index = glGetAttribLocation(m_program, name);
			ValidateOpenGL(L"Unable to get attribute index");
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
			ValidateOpenGL(L"Unable to get attribute value");
		}

		void OpenGLRenderContext::GetAttribute(int index, float* out)
		{
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
		}

		OpenGLRenderContext::~OpenGLRenderContext()
		{
			if (m_program)
			{
				glDeleteProgram(m_program);
				ValidateOpenGL(L"Unable to delete shader program");
			}
			m_program = 0;
		}
	}
}
