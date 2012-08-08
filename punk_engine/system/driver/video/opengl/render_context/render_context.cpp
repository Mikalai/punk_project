#include "render_context.h"
#include "render_context_impl.h"
#include <algorithm>

namespace OpenGL
{
	RenderContext::RenderContext()
		: impl_rc(new RenderContextImpl)
	{}

	RenderContext::RenderContext(const RenderContext& rc)
		: impl_rc(new RenderContextImpl(*rc.impl_rc))
	{}

	RenderContext& RenderContext::operator= (const RenderContext& rc)
	{
		RenderContext temp(rc);
		std::swap(*impl_rc, *rc.impl_rc);
		return *this;
	}

	RenderContext::~RenderContext()
	{
		impl_rc.reset(0);
	}

	void RenderContext::Init()
	{
		impl_rc->Init();
	}

	void RenderContext::Begin()
	{
		impl_rc->Begin();
	}

	void RenderContext::End()
	{
		impl_rc->End();
	}

	void RenderContext::SetFragmentShader(Shader* shader)
	{
		impl_rc->m_fragment_shader = shader;
	}

	void RenderContext::SetGeometryShader(Shader* shader)
	{
		impl_rc->m_geometry_shader = shader;
	}

	void RenderContext::SetVertexShader(Shader* shader)
	{
		impl_rc->m_vertex_shader = shader;
	}

	VertexAttributes RenderContext::GetSupportedVertexAttributes() const
	{
		return impl_rc->m_vertex_attributes;
	}

	bool RenderContext::SetUniformVector4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);

		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);

		glUniform4fv(loc, 1, value);

		return true;
	}

	bool RenderContext::SetUniformVector4f( int loc, const float* value )
	{
		glUniform4fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set uniform vec4");
		return true;
	}

	bool RenderContext::SetUniformVector3f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);
		if (loc < 0)
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform3fv(loc, 1, value);
		return true;
	}

	bool RenderContext::SetUniformVector3f(int loc, const float* value)
	{
		glUniform3fv(loc, 1, value);
		CHECK_GL_ERROR(L"Unable to set uniform vec3");
		return true;
	}

	bool RenderContext::SetUniformVector2f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform2fv(loc, 1, value);
		return true;
	}

	bool RenderContext::SetUniformVector2f(int loc, const float* value )
	{
		glUniform2fv(loc, 1, value);
		return true;
	}

	bool RenderContext::SetUniformFloat(const char * name, float value)
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1f(loc, value);
		return true;
	}

	bool RenderContext::SetUniformFloat(int loc, float value)
	{
		glUniform1f ( loc, value );
		return true;
	}

	bool RenderContext::SetUniformInt(const char * name, int value)
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1i ( loc, value );
		return true;
	}

	bool RenderContext ::SetUniformInt(int loc, int value)
	{
		glUniform1i( loc, value);
		return true;
	}

	bool RenderContext::SetUniformMatrix3f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( impl_rc->m_program, name );
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool RenderContext::SetUniformMatrix3f( int loc, const float* value)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool RenderContext::SetUniformMatrix4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( impl_rc->m_program, name );
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool RenderContext::SetUniformMatrix4f( int loc, const float* value)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		CHECK_GL_ERROR(L"Unable to set uniform mat4");
		return true;
	}

	bool RenderContext::SetUniformArrayMatrix4f(int loc, int count, const float* value)
	{
		glUniformMatrix4fv(loc, count, GL_FALSE, value);
		return true;
	}


	GLint RenderContext::GetUniformLocation(const char * name)
	{
		GLint res = glGetUniformLocation(impl_rc->m_program, name);
		return res;
	}

	void RenderContext::GetUniformVector(const char * name, float* out)
	{
		int loc = glGetUniformLocation(impl_rc->m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't get uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glGetUniformfv(impl_rc->m_program, loc, out);
	}

	bool RenderContext::SetTexture(const char * name, int texUnit)
	{
		int loc = glGetUniformLocation ( impl_rc->m_program, name );
	//	if ( loc == -1 )
		//	throw System::SystemError(L"Can't set texture: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1i(loc, texUnit);
		return true;
	}

	bool RenderContext::SetTexture(int loc, int texUnit)
	{
	//	if ( loc < 0 )
		//	throw System::SystemError(L"Can't set texture" + LOG_LOCATION_STRING);
		glUniform1i(loc, texUnit);
		return true;
	}

	bool RenderContext::BindAttributeTo(int loc, const char * name)
	{
		glBindAttribLocation(impl_rc->m_program, loc, name);
		return true;
	}

	bool RenderContext::SetAttribute(const char * name, const float* value)
	{
		int index = glGetAttribLocation(impl_rc->m_program, name);
		if ( index < 0 )
			throw System::SystemError(L"Can't set attribute: " + System::string(name) + LOG_LOCATION_STRING);
		glVertexAttrib4fv ( index, value );
		return true;
	}

	bool RenderContext::SetAttribute(int index, const float* value)
	{
		glVertexAttrib4fv(index, value);
		return true;
	}

	int RenderContext::IndexForAttrName(const char * name)
	{
		return glGetAttribLocation(impl_rc->m_program, name);
	}

	void RenderContext::GetAttribute(const char * name, float* out)
	{
		int index = glGetAttribLocation(impl_rc->m_program, name);
		if ( index < 0 )
			throw System::SystemError(L"Can't get attribute: " + System::string(name) + LOG_LOCATION_STRING);
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
	}

	void RenderContext::GetAttribute(int index, float* out)
	{
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
	}

	void RenderContext::EnableDepthTest(bool flag)
	{
		if (flag)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
}
