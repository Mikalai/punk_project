#include "shader.h"
#include "../../../../string/string.h"
#include "../../../../system/module.h"
#include "../../gl/module.h"
#include "../rc_dynamic.h"
#include <algorithm>

namespace GPU
{
	namespace OpenGL
	{
		Shader::Shader(ShaderType type) 
		{
			switch (type)
			{
			case ShaderType::Vertex:
				m_type = GL_VERTEX_SHADER;
				break;
			case ShaderType::Fragment:
				m_type = GL_FRAGMENT_SHADER;
				break;
			case ShaderType::Geometry:
				m_type = GL_GEOMETRY_SHADER;
				break;
			default:
				throw OpenGLInvalidValueException(L"Can't create suitable shader");
			}
		}

		Shader::~Shader()
		{
			try
			{
				if (m_shader_index)
				{
					glDeleteShader(m_shader_index);
					ValidateOpenGL(L"Unable to delete shader");
					m_shader_index = 0;
				}
			}
			catch(...)
			{
				//	avoid leaving destructor
			}
		}

		void Shader::CookFromString(const char* string, unsigned length)
		{
			m_shader_index = glCreateShader(m_type);
			ValidateOpenGL(L"Unable to create shader");
			out_message() << L"Loading vertex shader\n" + System::string(string, length) << std::endl;
			const char * body = string;
			int len = length;
			GLint compileStatus;
			glShaderSource(m_shader_index, 1, (const char**)&body,  &len);
			ValidateOpenGL(L"Unable to set shader source");
			glCompileShader(m_shader_index);
			ValidateOpenGL(L"Unable to compile shader");
			glGetShaderiv(m_shader_index, GL_COMPILE_STATUS, &compileStatus);
			ValidateOpenGL(L"Unable to get shader compile status");
			if (compileStatus == GL_TRUE)
			{
				out_message() << L"Shader has been compiled successfully" << std::endl;
			}
			else
			{
				GLint logLength;
				glGetShaderiv(m_shader_index, GL_INFO_LOG_LENGTH, &logLength);
				ValidateOpenGL(L"Unable to get shader info log length");
				if (logLength > 65536)
				{
					GLchar* buffer = new GLchar[logLength];
					glGetShaderInfoLog(m_shader_index, logLength, NULL, buffer);
					ValidateOpenGL(L"Unable to get shader info log text");
					out_error() << System::string(buffer) << std::endl;
					delete[] buffer;
				}
				else
				{
					GLchar buffer[65536];
					glGetShaderInfoLog(m_shader_index, 65536, NULL, buffer);
					ValidateOpenGL(L"Unable to get shader info log text");
					out_error() << System::string(buffer) << std::endl;
				}
				out_error() << L"Can't create vertex shader" << std::endl;
			}
		}

		void Shader::CookFromFile(const System::string& filename)
		{
			System::Buffer shader_data;
			System::BinaryFile::Load(filename, shader_data);		
			m_shader_index = glCreateShader(m_type);
			ValidateOpenGL(L"Unable to create shader");
			out_message() << L"Loading vertex shader " + filename << std::endl;
			char * body = (char*)shader_data.StartPointer();
			int len = shader_data.GetSize();
			GLint compileStatus;
			glShaderSource(m_shader_index, 1, (const char**)&body,  &len);
			ValidateOpenGL(L"Unable to set shader source");
			glCompileShader(m_shader_index);
			ValidateOpenGL(L"Unable to compile shader");
			glGetShaderiv(m_shader_index, GL_COMPILE_STATUS, &compileStatus);
			ValidateOpenGL(L"Unable to get shader compile status");
			if (compileStatus == GL_TRUE)
			{
				out_message() << filename + L" has been compiled successfully" << std::endl;
			}
			else
			{
				GLint logLength;
				glGetShaderiv(m_shader_index, GL_INFO_LOG_LENGTH, &logLength);
				ValidateOpenGL(L"Unable to get shader info log length");
				if (logLength > 65536)
				{
					GLchar* buffer = new GLchar[logLength];
					glGetShaderInfoLog(m_shader_index, logLength, NULL, buffer);
					ValidateOpenGL(L"Unable to get shader info log text");
					out_error() << System::string(buffer) << std::endl;
					delete[] buffer;
				}
				else
				{
					GLchar buffer[65536];
					glGetShaderInfoLog(m_shader_index, 65536, NULL, buffer);
					ValidateOpenGL(L"Unable to get shader info log text");
					out_error() << System::string(buffer) << std::endl;
				}
				out_error() << L"Can't create vertex shader" << std::endl;
			}
		}

		unsigned Shader::GetIndex() const
		{
			return m_shader_index;
		}

		void Shader::Connect(DynamicRenderContext *rc)
		{
			m_rc = rc;
		}
	}
}
