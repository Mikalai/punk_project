#include "../../../system/environment.h"
#include "gl_render_context.h"
#include "shaders/shader.h"
#include "../error/module.h"
#include "../gl/module.h"

namespace Gpu
{
	namespace OpenGL
	{
		OpenGLRenderContext::OpenGLRenderContext()
			: m_program(0)
		{
			m_vertex_shader = nullptr;
			m_fragment_shader = nullptr;
			m_geometry_shader = nullptr;
		}

        OpenGLRenderContext::OpenGLRenderContext(ShaderCollection VS, ShaderCollection FS, ShaderCollection GS)
			: m_program(0)
        {
			m_vertex_shader = nullptr;
			m_fragment_shader = nullptr;
			m_geometry_shader = nullptr;

            auto path = System::Environment::Instance()->GetShaderFolder();
			m_vertex_shader = new Shader(ShaderType::Vertex);
            m_vertex_shader->CookFromFile(path + GetShaderFile(VS));

			m_fragment_shader = new Shader(ShaderType::Fragment);
            m_fragment_shader->CookFromFile(path + GetShaderFile(FS));

            if (GS != ShaderCollection::No)
            {
				m_geometry_shader = new Shader(ShaderType::Geometry);
                m_geometry_shader->CookFromFile(path + GetShaderFile(GS));
            }

        }

		void OpenGLRenderContext::Begin()
		{
			Init();
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
					if (m_vertex_shader)
					{
						glAttachShader(m_program, m_vertex_shader->GetIndex());
						ValidateOpenGL(L"Unable to attach vertex shader to shader program");
					}
					else
					{
						out_error() << L"Vertex shader not set" << std::endl;
						return;
					}

					if (m_fragment_shader)
					{
						glAttachShader(m_program, m_fragment_shader->GetIndex());
						ValidateOpenGL(L"Unable to attach fragment shader to shader program");
					}
					else
					{
						out_error() << L"Fragment shader not set" << std::endl;
						return;
					}

					if (m_geometry_shader)
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

					InitUniforms();
				}
			}
			catch(...)
			{
				glDeleteProgram(m_program);
				m_program = 0;
                throw System::PunkException(L"Failed to create render context");
			}
		}

		bool OpenGLRenderContext::SetUniformVector4f(const char * name, const float* value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform4fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector4f(const char *name, const Math::vec4 &value)
        {
            return SetUniformVector4f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector4f( int index, const float* value )
		{
			if (index == -1)
				return false;
			glUniform4fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector4f(int index, const Math::vec4 &value)
        {
            return SetUniformVector4f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector3f(const char * name, const float* value )
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform3fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector3f(const char *name, const Math::vec3 &value)
        {
            return SetUniformVector3f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector3f(int index, const float* value)
		{
			if (index == -1)
				return false;
			glUniform3fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector3f(int index, const Math::vec3 &value)
        {
            return SetUniformVector3f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector2f(const char * name, const float* value )
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform2fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector2f(const char *name, const Math::vec2 &value)
        {
            return SetUniformVector2f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector2f(int index, const float* value )
		{
			if (index == -1)
				return false;
			glUniform2fv(index, 1, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector2f(int index, const Math::vec2 &value)
        {
            return SetUniformVector2f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformFloat(const char * name, float value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform1f(index, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformFloat(int index, float value)
		{
			if (index == -1)
				return false;
			glUniform1f ( index, value );
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(const char * name, int value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniform1i ( index, value );
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(int index, int value)
		{
			if (index == -1)
				return false;
			glUniform1i( index, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetUniformMatrix2f(const char * name, const float* value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniformMatrix2fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix2f(const char *name, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix2f( int index, const float* value)
		{		
			if (index == -1)
				return false;
			glUniformMatrix2fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix2f(int index, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix3f(const char * name, const float* value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniformMatrix3fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix3f(const char * name, const Math::mat3& value)
        {
            return SetUniformMatrix3f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix3f( int index, const float* value)
		{		
			if (index == -1)
				return false;
			glUniformMatrix3fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix3f(int index, const Math::mat3 &value)
        {
            return SetUniformMatrix3f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix4f(const char * name, const float* value)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get uniform location");
			glUniformMatrix4fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix4f(const char *name, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix4f( int index, const float* value)
		{
			if (index == -1)
				return false;
			glUniformMatrix4fv(index, 1, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix4f(int index, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformArrayMatrix4f(int index, int count, const float* value)
		{
			if (index == -1)
				return false;
			glUniformMatrix4fv(index, count, GL_FALSE, value);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

        bool OpenGLRenderContext::SetUniformArrayMatrix4f(int index, int count, const Math::mat4* value)
        {
            return SetUniformArrayMatrix4f(index, count, (float*)value);
        }


		int OpenGLRenderContext::GetUniformLocation(const char * name)
		{
			GLint res = glGetUniformLocation(m_program, name);
			ValidateOpenGL(L"Unable to get uniform location");
			return res;
		}

		void OpenGLRenderContext::GetUniformVector(const char * name, float* out)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return;
			ValidateOpenGL(L"Unable to get uniform location");
			glGetUniformfv(m_program, index, out);
		}

		bool OpenGLRenderContext::SetTexture(const char * name, int texUnit)
		{
			int index = glGetUniformLocation ( m_program, name );
			if (index == -1)
				return false;
			glUniform1i(index, texUnit);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::SetTexture(int index, int texUnit)
		{
			if (index == -1)
				return false;
			glUniform1i(index, texUnit);
			ValidateOpenGL(L"Unable to set value");
			return true;
		}

		bool OpenGLRenderContext::BindAttributeTo(int index, const char * name)
		{
			if (index == -1)
				return false;
			glBindAttribLocation(m_program, index, name);
			ValidateOpenGL(L"Unable to bind attribute");
			return true;
		}

		bool OpenGLRenderContext::SetAttribute(const char * name, const float* value)
		{
			int index = glGetAttribLocation(m_program, name);
			if (index == -1)
				return false;
			ValidateOpenGL(L"Unable to get attribute location");
			glVertexAttrib4fv ( index, value );
			ValidateOpenGL(L"Unable to set attribute");
			return true;
		}

		bool OpenGLRenderContext::SetAttribute(int index, const float* value)
		{
			if (index == -1)
				return false;
			glVertexAttrib4fv(index, value);
			ValidateOpenGL(L"Unable to get attribute value");
			return true;
		}

		int OpenGLRenderContext::IndexForAttrName(const char * name)
		{
			int index = glGetAttribLocation(m_program, name);
			if (index == -1)
				return -1;
			ValidateOpenGL(L"Unable to get attribute index");
			return index;
		}

		void OpenGLRenderContext::GetAttribute(const char * name, float* out)
		{
			int index = glGetAttribLocation(m_program, name);
			if (index == -1)
				return;
			ValidateOpenGL(L"Unable to get attribute index");
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
			ValidateOpenGL(L"Unable to get attribute value");
		}

		void OpenGLRenderContext::GetAttribute(int index, float* out)
		{
			if (index == -1)
				return;
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
		}

		OpenGLRenderContext::~OpenGLRenderContext()
		{
			delete m_vertex_shader;
			m_vertex_shader = nullptr;
			delete m_fragment_shader;
			m_fragment_shader = nullptr;
			delete m_geometry_shader;
			m_geometry_shader = nullptr;

			if (m_program)
			{
				glDeleteProgram(m_program);
				ValidateOpenGL(L"Unable to delete shader program");
			}
			m_program = 0;
		}

		void OpenGLRenderContext::SetUpOpenGL(const CoreState &state)
		{
            glLineWidth(state.render_state->m_line_width);
            ValidateOpenGL(L"Can't set line width");
            glPointSize(state.render_state->m_point_size);
            ValidateOpenGL(L"Can't set point size");

			if (state.render_state->m_enable_wireframe)
			{				
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				ValidateOpenGL(L"Can't change polygon mode");
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				ValidateOpenGL(L"Can't change polygon mode");
			}

			if (state.render_state->m_depth_test)
			{
				glEnable(GL_DEPTH_TEST);
				ValidateOpenGL(L"Can't enable depth test");
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				ValidateOpenGL(L"Can't disable depth test");
			}

			if (state.render_state->m_enable_blending)
			{
				glEnable(GL_BLEND);
				auto src = BlendFunctionToOpenGL(state.render_state->m_blend_src);
				auto dst = BlendFunctionToOpenGL(state.render_state->m_blend_dst);
				auto color = state.render_state->m_blend_color;
				glBlendFunc(src, dst);
				glBlendColor(color[0], color[1], color[2], color[3]);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}
	}
}
