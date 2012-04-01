#include "shader.h"
#include "shader_impl.h"
#include "../../../../string.h"
#include "../../../../buffer.h"
#include "../../../../binary_file.h"
#include "../../../../error.h"
#include "../../../../logger.h"
#include "../extensions.h"
#include "../gl/gl3.h"

#include <algorithm>

namespace OpenGL
{
		Shader::Shader(ShaderType type) 
		: impl_shader(new ShaderImpl(type))
	{}

	Shader::Shader(const Shader& shader)
		: impl_shader(new ShaderImpl(*shader.impl_shader))
	{}

	Shader& Shader::operator= (const Shader& shader)
	{
		Shader temp(shader);
		std::swap(impl_shader, temp.impl_shader);
		return *this;
	}

	Shader::~Shader()
	{
		impl_shader.reset(0);
	}

	void Shader::CookFromString(const char* string, unsigned length)
	{
		impl_shader->m_shader_index = glCreateShader(impl_shader->m_type);
		CHECK_GL_ERROR(L"Unable to create shader");
		System::Logger::GetInstance()->WriteMessage(L"Loading vertex shader\n" + System::string(string, length));
		const char * body = string;
		int len = length;
		GLint compileStatus;
		glShaderSource(impl_shader->m_shader_index, 1, (const char**)&body,  &len);
		CHECK_GL_ERROR(L"Unable to set shader source");
		glCompileShader(impl_shader->m_shader_index);
		CHECK_GL_ERROR(L"Unable to compile shader");
		glGetShaderiv(impl_shader->m_shader_index, GL_COMPILE_STATUS, &compileStatus);
		CHECK_GL_ERROR(L"Unable to get shader compile status");
		if (compileStatus == GL_TRUE)
		{
			System::Logger::GetInstance()->WriteMessage(L"Shader has been compiled successfully");
		}
		else
		{
			GLint logLength;
			glGetShaderiv(impl_shader->m_shader_index, GL_INFO_LOG_LENGTH, &logLength);
			CHECK_GL_ERROR(L"Unable to get shader info log length");
			if (logLength > 65536)
			{
				GLchar* buffer = new GLchar[logLength];
				glGetShaderInfoLog(impl_shader->m_shader_index, logLength, NULL, buffer);
				CHECK_GL_ERROR(L"Unable to get shader info log text");
				System::Logger::GetInstance()->WriteError(System::string(buffer));			
				delete[] buffer;
			}
			else
			{
				GLchar buffer[65536];
				glGetShaderInfoLog(impl_shader->m_shader_index, 65536, NULL, buffer);
				CHECK_GL_ERROR(L"Unable to get shader info log text");
				System::Logger::GetInstance()->WriteError(System::string(buffer));							
			}
			throw System::SystemError(L"Can't create vertex shader");
		}
	}

	void Shader::CookFromFile(const System::string& filename)
	{
		System::Buffer shader_data;
		System::BinaryFile::Load(filename, shader_data);		
		impl_shader->m_shader_index = glCreateShader(impl_shader->m_type);
		CHECK_GL_ERROR(L"Unable to create shader");
		System::Logger::GetInstance()->WriteMessage(L"Loading vertex shader " + filename);
		char * body = (char*)shader_data.StartPointer();
		int len = shader_data.GetSize();
		GLint compileStatus;
		glShaderSource(impl_shader->m_shader_index, 1, (const char**)&body,  &len);
		CHECK_GL_ERROR(L"Unable to set shader source");
		glCompileShader(impl_shader->m_shader_index);
		CHECK_GL_ERROR(L"Unable to compile shader");
		glGetShaderiv(impl_shader->m_shader_index, GL_COMPILE_STATUS, &compileStatus);
		CHECK_GL_ERROR(L"Unable to get shader compile status");
		if (compileStatus == GL_TRUE)
		{
			System::Logger::GetInstance()->WriteMessage(filename + L" has been compiled successfully");
		}
		else
		{
			GLint logLength;
			glGetShaderiv(impl_shader->m_shader_index, GL_INFO_LOG_LENGTH, &logLength);
			CHECK_GL_ERROR(L"Unable to get shader info log length");
			if (logLength > 65536)
			{
				GLchar* buffer = new GLchar[logLength];
				glGetShaderInfoLog(impl_shader->m_shader_index, logLength, NULL, buffer);
				CHECK_GL_ERROR(L"Unable to get shader info log text");
				System::Logger::GetInstance()->WriteError(System::string(buffer));			
				delete[] buffer;
			}
			else
			{
				GLchar buffer[65536];
				glGetShaderInfoLog(impl_shader->m_shader_index, 65536, NULL, buffer);
				CHECK_GL_ERROR(L"Unable to get shader info log text");
				System::Logger::GetInstance()->WriteError(System::string(buffer));							
			}
			throw System::SystemError(L"Can't create vertex shader");
		}
	}

	unsigned Shader::GetIndex() const
	{
		return impl_shader->m_shader_index;
	}
}