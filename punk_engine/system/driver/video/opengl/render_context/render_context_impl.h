#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_IMPL
#define _H_PUNK_OPENGL_RENDER_CONTEXT_IMPL

#include "render_context.h"
#include "shader.h"
#include "../gl/gl3.h"
#include "../extensions.h"
#include "../../../../error.h"
#include "../vertex_attributes.h"

namespace OpenGL
{
	struct RenderContextImpl
	{
		Shader* m_vertex_shader;
		Shader* m_fragment_shader;
		Shader* m_geometry_shader;
		GLuint m_program;
		bool m_was_modified;
		VertexAttributes m_vertex_attributes;

		RenderContextImpl()
			: m_vertex_shader(nullptr)
			, m_fragment_shader(nullptr)
			, m_geometry_shader(nullptr)
			, m_program(0)
			, m_was_modified(false)
			, m_vertex_attributes(0)
		{}

		RenderContextImpl(const RenderContextImpl& impl)
			: m_vertex_shader(impl.m_vertex_shader)
			, m_fragment_shader(impl.m_fragment_shader)
			, m_geometry_shader(impl.m_geometry_shader)
			, m_program(impl.m_program)
			, m_was_modified(impl.m_was_modified)
			, m_vertex_attributes(impl.m_vertex_attributes)
		{}

		void Begin()
		{
			if (m_was_modified || !m_program)
			{
				if (m_program)
				{
					glDeleteProgram(m_program);
					CHECK_GL_ERROR(L"Unable to delete shader program");
				}
				m_program = glCreateProgram();
				CHECK_GL_ERROR(L"Unable to create shader program");
				if (m_vertex_shader)
				{
					glAttachShader(m_program, m_vertex_shader->GetIndex());
					CHECK_GL_ERROR(L"Unable to attach vertex shader to shader program");
				}
				else
					throw System::SystemError(L"Vertex shader not set");

				if (m_fragment_shader)
				{
					glAttachShader(m_program, m_fragment_shader->GetIndex());
					CHECK_GL_ERROR(L"Unable to attach fragment shader to shader program");
				}
				else
					throw System::SystemError(L"Fragment shader not set");
				if (m_geometry_shader)
				{
					glAttachShader(m_program, m_geometry_shader->GetIndex());				
					CHECK_GL_ERROR(L"Unable to attach geometry shader to shader program");
				}

				glLinkProgram(m_program);
				CHECK_GL_ERROR(L"Unable to link shader program");

				GLint status;
				glGetProgramiv(m_program, GL_LINK_STATUS, &status);
				CHECK_GL_ERROR(L"Unable to get link status of the shader program");
				if (status == GL_TRUE)
				{
					glValidateProgram(m_program);
					CHECK_GL_ERROR(L"Unable to validate shader program");
					glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
					CHECK_GL_ERROR(L"Unable to get validation status of the shader program");
					if (status != GL_TRUE)
						throw System::SystemError(L"Shader program validation failed");

				}
				else
					throw System::SystemError(L"Unable to link shader program");

				InitUniforms();

				m_was_modified = false;
			}
			glUseProgram(m_program);
			CHECK_GL_ERROR(L"Unable to use shader program");
			BindUniforms();
			glEnable(GL_DEPTH_TEST);
		}

		void End()
		{
			glUseProgram(0);
		}

		bool SetUniformVector4f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");
			glUniform4fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformVector4f( int loc, const float* value )
		{
			glUniform4fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformVector3f(const char * name, const float* value )
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniform3fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformVector3f(int loc, const float* value)
		{
			glUniform3fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformVector2f(const char * name, const float* value )
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniform2fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformVector2f(int loc, const float* value )
		{
			glUniform2fv(loc, 1, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformFloat(const char * name, float value)
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniform1f(loc, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformFloat(int loc, float value)
		{
			glUniform1f ( loc, value );
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformInt(const char * name, int value)
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniform1i ( loc, value );
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformInt(int loc, int value)
		{
			glUniform1i( loc, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformMatrix3f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation ( m_program, name );
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformMatrix3f( int loc, const float* value)
		{
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformMatrix4f(const char * name, const float* value)
		{
			int loc = glGetUniformLocation ( m_program, name );
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformMatrix4f( int loc, const float* value)
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetUniformArrayMatrix4f(int loc, int count, const float* value)
		{
			glUniformMatrix4fv(loc, count, GL_FALSE, value);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}


		GLint GetUniformLocation(const char * name)
		{
			GLint res = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			return res;
		}

		void GetUniformVector(const char * name, float* out)
		{
			int loc = glGetUniformLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get uniform location");				
			glGetUniformfv(m_program, loc, out);
		}

		bool SetTexture(const char * name, int texUnit)
		{
			int loc = glGetUniformLocation ( m_program, name );
			//	if ( loc == -1 )
			//	throw System::SystemError(L"Can't set texture: " + System::string(name));
			glUniform1i(loc, texUnit);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool SetTexture(int loc, int texUnit)
		{
			//	if ( loc < 0 )
			//	throw System::SystemError(L"Can't set texture");
			glUniform1i(loc, texUnit);
			CHECK_GL_ERROR(L"Unable to set value");
			return true;
		}

		bool BindAttributeTo(int loc, const char * name)
		{
			glBindAttribLocation(m_program, loc, name);
			CHECK_GL_ERROR(L"Unable to bind attribute");
			return true;
		}

		bool SetAttribute(const char * name, const float* value)
		{
			int index = glGetAttribLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get attribute location");
			glVertexAttrib4fv ( index, value );
			CHECK_GL_ERROR(L"Unable to set attribute");
			return true;
		}

		bool SetAttribute(int index, const float* value)
		{
			glVertexAttrib4fv(index, value);
			CHECK_GL_ERROR(L"Unable to get attribute value");
			return true;
		}

		int IndexForAttrName(const char * name)
		{
			int res = glGetAttribLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get attribute index");
			return res;
		}

		void GetAttribute(const char * name, float* out)
		{
			int index = glGetAttribLocation(m_program, name);
			CHECK_GL_ERROR(L"Unable to get attribute index");
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
			CHECK_GL_ERROR(L"Unable to get attribute value");
		}

		void GetAttribute(int index, float* out)
		{
			glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
		}

		virtual void InitUniforms()
		{
			throw System::SystemError(L"Not implemented");
		}

		virtual void BindUniforms() 
		{
			throw System::SystemError(L"Not implemented");
		}

		virtual void InitAttributes()
		{
			throw System::SystemError(L"Not implemented");
		}

		virtual ~RenderContextImpl()
		{
			if (m_program)
			{
				glDeleteProgram(m_program);
				CHECK_GL_ERROR(L"Unable to delete shader program");
			}
			m_program = 0;
		}
	};
}

#endif