#include "dummy_render_context_policy.h"
#include "../../system/logger.h"
#include "../extensions.h"

namespace OpenGL
{
	DummyRenderPolicy::DummyRenderPolicy()
		: m_program(0)
		, m_was_modified(false)
		, m_vertex_attributes(Utility::COMPONENT_NONE)
	{}

	void DummyRenderPolicy::InitUniforms()
	{
		out_warning() << "InitUniforms() not implemented" << std::endl;		
	}

	void DummyRenderPolicy::BindParameters(const DummyParameters& params)
	{	
		out_warning() << "BindParameters() not implemented" << std::endl;
	}

	Utility::VertexAttributes DummyRenderPolicy::GetRequiredAttributesSet() const 
	{
		return Utility::COMPONENT_NONE;
	}

	void DummyRenderPolicy::Begin()
	{
		glUseProgram(m_program);
		//out_warning() << "Begin() not implemented" << std::endl;
	}

	void DummyRenderPolicy::End()
	{
		glUseProgram(0);
		//out_warning() << "End() not implemented" << std::endl;
	}


	void DummyRenderPolicy::Init()
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
			if (m_vertex_shader.get())
			{
				glAttachShader(m_program, m_vertex_shader->GetIndex());
				CHECK_GL_ERROR(L"Unable to attach vertex shader to shader program");
			}
			else
			{
				out_error() << L"Vertex shader not set" << std::endl;
				return;
			}

			if (m_fragment_shader.get())
			{
				glAttachShader(m_program, m_fragment_shader->GetIndex());
				CHECK_GL_ERROR(L"Unable to attach fragment shader to shader program");
			}
			else
			{
				out_error() << L"Fragment shader not set" << std::endl;
				return;
			}

			if (m_geometry_shader.get())
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

	bool DummyRenderPolicy::SetUniformVector4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");
		glUniform4fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformVector4f( int loc, const float* value )
	{
		glUniform4fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformVector3f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniform3fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformVector3f(int loc, const float* value)
	{
		glUniform3fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformVector2f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniform2fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformVector2f(int loc, const float* value )
	{
		glUniform2fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformFloat(const char * name, float value)
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniform1f(loc, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformFloat(int loc, float value)
	{
		glUniform1f ( loc, value );
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformInt(const char * name, int value)
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniform1i ( loc, value );
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformInt(int loc, int value)
	{
		glUniform1i( loc, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformMatrix3f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( m_program, name );
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformMatrix3f( int loc, const float* value)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformMatrix4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( m_program, name );
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformMatrix4f( int loc, const float* value)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetUniformArrayMatrix4f(int loc, int count, const float* value)
	{
		glUniformMatrix4fv(loc, count, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}


	int DummyRenderPolicy::GetUniformLocation(const char * name)
	{
		GLint res = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		return res;
	}

	void DummyRenderPolicy::GetUniformVector(const char * name, float* out)
	{
		int loc = glGetUniformLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get uniform location");				
		glGetUniformfv(m_program, loc, out);
	}

	bool DummyRenderPolicy::SetTexture(const char * name, int texUnit)
	{
		int loc = glGetUniformLocation ( m_program, name );
		//	if ( loc == -1 )
		//	throw System::SystemError(L"Can't set texture: " + System::string(name));
		glUniform1i(loc, texUnit);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::SetTexture(int loc, int texUnit)
	{
		//	if ( loc < 0 )
		//	throw System::SystemError(L"Can't set texture");
		glUniform1i(loc, texUnit);
		CHECK_GL_ERROR(L"Unable to set value");
		return true;
	}

	bool DummyRenderPolicy::BindAttributeTo(int loc, const char * name)
	{
		glBindAttribLocation(m_program, loc, name);
		CHECK_GL_ERROR(L"Unable to bind attribute");
		return true;
	}

	bool DummyRenderPolicy::SetAttribute(const char * name, const float* value)
	{
		int index = glGetAttribLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get attribute location");
		glVertexAttrib4fv ( index, value );
		CHECK_GL_ERROR(L"Unable to set attribute");
		return true;
	}

	bool DummyRenderPolicy::SetAttribute(int index, const float* value)
	{
		glVertexAttrib4fv(index, value);
		CHECK_GL_ERROR(L"Unable to get attribute value");
		return true;
	}

	int DummyRenderPolicy::IndexForAttrName(const char * name)
	{
		int res = glGetAttribLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get attribute index");
		return res;
	}

	void DummyRenderPolicy::GetAttribute(const char * name, float* out)
	{
		int index = glGetAttribLocation(m_program, name);
		CHECK_GL_ERROR(L"Unable to get attribute index");
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
		CHECK_GL_ERROR(L"Unable to get attribute value");
	}

	void DummyRenderPolicy::GetAttribute(int index, float* out)
	{
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
	}

	DummyRenderPolicy::~DummyRenderPolicy()
	{
		if (m_program)
		{
			glDeleteProgram(m_program);
			CHECK_GL_ERROR(L"Unable to delete shader program");
		}
		m_program = 0;
	}
}
