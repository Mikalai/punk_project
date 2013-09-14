#include "shader.h"
#include "../../../../string/string.h"
#include "../../../../system/module.h"
#include "../../gl/module.h"
#include "../rc_dynamic.h"
#include <algorithm>

namespace Gpu
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
            if (m_shader_index)
            {
                GL_CALL(glDeleteShader(m_shader_index));
                m_shader_index = 0;
            }
        }

		void Shader::CookFromString(const char* string, unsigned length)
		{
            GL_CALL(m_shader_index = glCreateShader(m_type));
			const char * body = string;
			int len = length;
			GLint compileStatus;
            GL_CALL(glShaderSource(m_shader_index, 1, (const char**)&body,  &len));
            GL_CALL(glCompileShader(m_shader_index));
            GL_CALL(glGetShaderiv(m_shader_index, GL_COMPILE_STATUS, &compileStatus));
			if (compileStatus == GL_TRUE)
			{
				out_message() << L"Shader has been compiled successfully" << std::endl;
			}
			else
			{
				GLint logLength;
                GL_CALL(glGetShaderiv(m_shader_index, GL_INFO_LOG_LENGTH, &logLength));
                std::vector<char> buffer(logLength);
                GL_CALL(glGetShaderInfoLog(m_shader_index, logLength, NULL, &buffer[0]));
                throw System::PunkException(L"Can't create vertex shader: \n" + System::string(&buffer[0], buffer.size()) + L'\n');
			}
		}

        void Shader::CookFromStringWithHeaders(const char *data, unsigned length, int count, const char **names)
        {
            GL_CALL(m_shader_index = glCreateShader(m_type));
            const char * body = data;
            int len = length;
            GLint compileStatus;
            GL_CALL(glShaderSource(m_shader_index, 1, (const char**)&body,  &len));
            GL_CALL(glCompileShaderIncludeARB(m_shader_index, count, names, nullptr));
            GL_CALL(glGetShaderiv(m_shader_index, GL_COMPILE_STATUS, &compileStatus));
            if (compileStatus == GL_TRUE)
            {
                out_message() << L"Shader has been compiled successfully" << std::endl;
            }
            else
            {
                GLint logLength;
                GL_CALL(glGetShaderiv(m_shader_index, GL_INFO_LOG_LENGTH, &logLength));
                std::vector<char> buffer(logLength);
                GL_CALL(glGetShaderInfoLog(m_shader_index, logLength, NULL, &buffer[0]));
                throw System::PunkException(L"Can't create vertex shader: \n" + System::string(&buffer[0], buffer.size()) + L'\n');
            }
        }

		void Shader::CookFromFile(const System::string& filename)
		{
			System::Buffer shader_data;
			System::BinaryFile::Load(filename, shader_data);		
            GL_CALL(m_shader_index = glCreateShader(m_type));
			out_message() << L"Loading vertex shader " + filename << std::endl;
            const char* body = (const char*)shader_data.StartPointer();
			int len = shader_data.GetSize();
            CookFromString(body, len);
		}

        void Shader::CookFromFileWithHeaders(const System::string &filename, int count, const char **names)
        {
            System::Buffer shader_data;
            System::BinaryFile::Load(filename, shader_data);
            GL_CALL(m_shader_index = glCreateShader(m_type));
            out_message() << L"Loading vertex shader " + filename << std::endl;
            const char* body = (const char*)shader_data.StartPointer();
            int len = shader_data.GetSize();
            CookFromStringWithHeaders(body, len, count, names);
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
