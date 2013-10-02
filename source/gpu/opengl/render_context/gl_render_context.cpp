#include <sstream>
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
            GL_CALL(glUseProgram(m_program));
		}

		void OpenGLRenderContext::End()
		{
            GL_CALL(glUseProgram(0));
		}

		void OpenGLRenderContext::Init()
		{
			try
			{
				if (m_was_modified || !m_program)
				{
					if (m_program)
					{
                        GL_CALL(glDeleteProgram(m_program));
					}
                    GL_CALL(m_program = glCreateProgram());
					if (m_vertex_shader)
					{
                        GL_CALL(glAttachShader(m_program, m_vertex_shader->GetIndex()));
					}
					else
					{
                        throw System::PunkException(L"Vertex shader not set");
					}

					if (m_fragment_shader)
					{
                        GL_CALL(glAttachShader(m_program, m_fragment_shader->GetIndex()));
					}
					else
					{
                        throw System::PunkException(L"Fragment shader not set");
					}

					if (m_geometry_shader)
					{
                        GL_CALL(glAttachShader(m_program, m_geometry_shader->GetIndex()));
					}

                    GL_CALL(glLinkProgram(m_program));

					GLint status;
                    GL_CALL(glGetProgramiv(m_program, GL_LINK_STATUS, &status));
					if (status == GL_TRUE)
					{
                        GL_CALL(glValidateProgram(m_program));
                        GL_CALL(glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status));
						if (status != GL_TRUE)
						{
                            throw System::PunkException(L"Shader program validation failed");
						}

					}
					else
					{
                        throw System::PunkException(L"Unable to link shader program");
					}
					m_was_modified = false;

					InitUniforms();
				}
			}
			catch(...)
			{
                GL_CALL(glDeleteProgram(m_program));
				m_program = 0;
                throw;
			}
		}

#define STRICT 0

		bool OpenGLRenderContext::SetUniformVector4f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform4fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector4f(const char *name, const Math::vec4 &value)
        {
            return SetUniformVector4f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector4f( int index, const float* value )
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform4fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector4f(int index, const Math::vec4 &value)
        {
            return SetUniformVector4f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector3f(const char * name, const float* value )
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform3fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector3f(const char *name, const Math::vec3 &value)
        {
            return SetUniformVector3f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector3f(int index, const float* value)
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform3fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector3f(int index, const Math::vec3 &value)
        {
            return SetUniformVector3f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector2f(const char * name, const float* value )
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform2fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector2f(const char *name, const Math::vec2 &value)
        {
            return SetUniformVector2f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformVector2f(int index, const float* value )
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform2fv(index, 1, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformVector2f(int index, const Math::vec2 &value)
        {
            return SetUniformVector2f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformFloat(const char * name, float value)
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1f(index, value));
			return true;
		}

		bool OpenGLRenderContext::SetUniformFloat(int index, float value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1f(index, value));
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(const char * name, int value)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, value));
			return true;
		}

		bool OpenGLRenderContext::SetUniformInt(int index, int value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i( index, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformBool(int index, bool value)
        {
            if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i( index, (int)value));
            return true;
        }

		bool OpenGLRenderContext::SetUniformMatrix2f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix2fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix2f(const char *name, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(name, &value[0]);
        }

        bool OpenGLRenderContext::SetUniformMatrix2f(int index, const float* value)
		{		
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix2fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix2f(int index, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix3f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation (m_program, name));
            if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix3fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix3f(const char * name, const Math::mat3& value)
        {
            return SetUniformMatrix3f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix3f( int index, const float* value)
		{		
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix3fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix3f(int index, const Math::mat3 &value)
        {
            return SetUniformMatrix3f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix4f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation (m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix4f(const char *name, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(name, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformMatrix4f( int index, const float* value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformMatrix4f(int index, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(index, &value[0]);
        }

		bool OpenGLRenderContext::SetUniformArrayMatrix4f(int index, int count, const float* value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, count, GL_FALSE, value));
			return true;
		}

        bool OpenGLRenderContext::SetUniformArrayMatrix4f(int index, int count, const Math::mat4* value)
        {
            return SetUniformArrayMatrix4f(index, count, (float*)value);
        }

        bool OpenGLRenderContext::SetUniformLight(const LightSourceShaderParameters &light, const LightParameters &value)
        {
            SetUniformInt(light.enabled, value.IsEnabled());
            if (value.IsEnabled())
            {
                SetUniformVector4f(light.direction, value.GetDirection());
                SetUniformVector4f(light.position, value.GetPosition());
                SetUniformVector4f(light.diffuse_color, value.GetDiffuseColor());
                SetUniformVector4f(light.ambient_color, value.GetAmbientColor());
                SetUniformFloat(light.attenuation_constant, value.GetLightConstantAttenuation());
                SetUniformFloat(light.attenuation_linear, value.GetLightLinearAttenuation());
                SetUniformFloat(light.attenuation_quadric, value.GetLightQuadricAttenuation());
                SetUniformFloat(light.spot, value.GetSpotExponent());
                SetUniformInt(light.type, (int)value.GetType());
                SetUniformInt(light.attenuation_model, (int)value.GetLightAttenuation());
            }
            return true;
        }

        bool OpenGLRenderContext::SetUniformMaterial(const MaterialShaderParameters &material, const Material &value)
        {
            SetUniformVector4f(material.diffuse, value.m_diffuse_color);
            SetUniformVector4f(material.specular, value.m_specular_color);
            SetUniformFloat(material.shininess, value.m_specular_factor);
        }

		int OpenGLRenderContext::GetUniformLocation(const char * name)
		{
            GL_CALL(GLint res = glGetUniformLocation(m_program, name));
            if (res == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                return -1;
#endif
            }
			return res;
		}

		void OpenGLRenderContext::GetUniformVector(const char * name, float* out)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed get uniform {0}").arg(name));
#else
                ;
#endif
            }
            GL_CALL(glGetUniformfv(m_program, index, out));
		}

		bool OpenGLRenderContext::SetTexture(const char * name, int texUnit)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set texture {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, texUnit));
			return true;
		}

		bool OpenGLRenderContext::SetTexture(int index, int texUnit)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed set texture {0}").arg(texUnit));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, texUnit));
			return true;
		}

		bool OpenGLRenderContext::BindAttributeTo(int index, const char * name)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed to bind attribute {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glBindAttribLocation(m_program, index, name));
			return true;
		}

		bool OpenGLRenderContext::SetAttribute(const char * name, const float* value)
		{
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed to set attribute {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glVertexAttrib4fv ( index, value ));
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
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed to get attribute {0}").arg(name));
#else
                return -1;
#endif
            }
            return index;
		}

		void OpenGLRenderContext::GetAttribute(const char * name, float* out)
		{
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(System::string("Failed to get attribute {0}").arg(name));
#else
                ;
#endif
            }
            GL_CALL(glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out));
		}

		void OpenGLRenderContext::GetAttribute(int index, float* out)
		{
			if (index == -1)
				return;
            GL_CALL(glGetVertexAttribfv(index, GL_CURRENT_VERTEX_ATTRIB, out));
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
                GL_CALL(glDeleteProgram(m_program));
			}
			m_program = 0;
		}

		void OpenGLRenderContext::SetUpOpenGL(const CoreState &state)
		{
            GL_CALL(glLineWidth(state.render_state->m_line_width));
            GL_CALL(glPointSize(state.render_state->m_point_size));

			if (state.render_state->m_enable_wireframe)
			{				
                GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			}
			else
			{
                GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			}

			if (state.render_state->m_depth_test)
			{
                GL_CALL(glEnable(GL_DEPTH_TEST));
			}
			else
			{
                GL_CALL(glDisable(GL_DEPTH_TEST));
			}

			if (state.render_state->m_enable_blending)
			{
                GL_CALL(glEnable(GL_BLEND));
				auto src = BlendFunctionToOpenGL(state.render_state->m_blend_src);
				auto dst = BlendFunctionToOpenGL(state.render_state->m_blend_dst);
				auto color = state.render_state->m_blend_color;
                GL_CALL(glBlendFunc(src, dst));
                GL_CALL(glBlendColor(color[0], color[1], color[2], color[3]));
			}
			else
			{
                GL_CALL(glDisable(GL_BLEND));
			}
		}

        const LightSourceShaderParameters OpenGLRenderContext::GetUniformLightLocation(const char* name)
        {
            LightSourceShaderParameters uLight;
            {
                std::stringstream stream;
                stream << name << ".ambient_color";
                uLight.ambient_color = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_constant";
                uLight.attenuation_constant = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_linear";
                uLight.attenuation_linear = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_model";
                uLight.attenuation_model = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_quadric";
                uLight.attenuation_quadric = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".diffuse_color";
                uLight.diffuse_color = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".direction";
                uLight.direction = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".position";
                uLight.position = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".spot";
                uLight.spot = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".type";
                uLight.type = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".enabled";
                uLight.enabled = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".specular_color";
                uLight.specular_color = GetUniformLocation(stream.str().c_str());
            }
            return uLight;
        }

        const MaterialShaderParameters OpenGLRenderContext::GetUniformaMaterialLocation(const char* name)
        {
            MaterialShaderParameters material;
            {
                std::stringstream stream;
                stream << name << ".diffuse";
                material.diffuse = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".shininess";
                material.shininess = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".specular";
                material.specular = GetUniformLocation(stream.str().c_str());
            }

            return material;
        }

        const FogShaderParameters OpenGLRenderContext::GetUniformFogLocation(const char* name)
        {
            FogShaderParameters fog;
            return fog;
        }
	}
}
