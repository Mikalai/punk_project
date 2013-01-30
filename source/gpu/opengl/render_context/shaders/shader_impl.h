#ifndef _H_SHADER_IMPL
#define _H_SHADER_IMPL

#include "../../gl/module.h"
#include "../../error/module.h"
#include "shader.h"

namespace GPU
{
	namespace OpenGL
	{
		struct ShaderImpl
		{
			GLuint m_shader_index;
			GLenum m_type;

			explicit ShaderImpl(Shader::ShaderType type) 
				: m_shader_index(0)
			{
				switch (type)
				{
				case Shader::SHADER_VERTEX:
					m_type = GL_VERTEX_SHADER;
					break;
				case Shader::SHADER_FRAGMENT:
					m_type = GL_FRAGMENT_SHADER;
					break;
				case Shader::SHADER_GEOMETRY:
					m_type = GL_GEOMETRY_SHADER;
					break;
				default:
					throw OpenGLInvalidValueException(L"Can't create suitable shader");
				}
			}

			ShaderImpl(const ShaderImpl& impl)
				: m_shader_index(impl.m_shader_index)
				, m_type(impl.m_type)
			{}

			const wchar_t* ShaderType()
			{
				switch (m_type)
				{
				case GL_VERTEX_SHADER:
					return L"vertex";
				case GL_FRAGMENT_SHADER:
					return L"fragment";
				case GL_GEOMETRY_SHADER:
					return L"geometry";
				default:
					return L"unknown";
				}
			}

			~ShaderImpl()
			{
				try
				{
					if (m_shader_index)
					{
						glDeleteShader(m_shader_index);
						CHECK_GL_ERROR(L"Unable to delete shader");
						m_shader_index = 0;
					}
				}
				catch(...)
				{
					//	avoid leaving destructor
				}
			}
		};
	}
}

#endif