#include "rc_bump_mapping.h"

namespace GPU
{
	namespace OpenGL
	{

		RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderBump);
			m_fragment_shader.reset(new FragmentShaderBump);
			Init();
		}

		void RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}			
		}

		void RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProj = GetUniformLocation("uProj");
			uNormalMatrix = GetUniformLocation("uNormalMatrix");
			uLightPosition = GetUniformLocation("uLightPosition");
			uAmbient = GetUniformLocation("uAmbient");
			uSpecular = GetUniformLocation("uSpecular");
			uDiffuse = GetUniformLocation("uDiffuse");
			uSpecularPower = GetUniformLocation("uSpecularPower");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uNormalMap = GetUniformLocation("uNormalMap");
		}

		void RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::BindParameters(const CoreState& pparams)
		{									
			//Math::mat4 p = Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
			//Math::mat4 p2 = pparams.m_camera->GetProjectionMatrix();
			//Math::mat4 v = Math::mat4::CreateTargetCameraMatrix(Math::vec3(0, 5, 5), Math::vec3(0,0,0), Math::vec3(0,1,0));
			//Math::mat4 w = Math::mat4::CreateIdentity();			
			Math::mat3 normal_matrix = (pparams.m_view * pparams.m_world).Inversed().Transposed().RotationPart();
			SetUniformMatrix4f(uWorld, &pparams.m_world[0]);
			//SetUniformMatrix4f(uWorld, &w[0]);
			SetUniformMatrix4f(uView, &pparams.m_view[0]);
			//SetUniformMatrix4f(uView, &v[0]);
			SetUniformMatrix4f(uProj, &pparams.m_projection[0]);
			//SetUniformMatrix4f(uProj, &p[0]);
			SetUniformMatrix3f(uNormalMatrix, &normal_matrix[0]);
			if (!pparams.m_lights.empty())
				SetUniformVector3f(uLightPosition, &pparams.m_lights[0]->GetPosition()[0]);
			else
			{
				Math::vec3 v(0,0,0);
				SetUniformVector3f(uLightPosition, &v[0]);
			}

			SetUniformVector4f(uAmbient, &(Math::vec4(pparams.m_ambient_color))[0]);
			SetUniformVector4f(uSpecular, &pparams.m_specular_color[0]);
			SetUniformVector4f(uDiffuse, &pparams.m_diffuse_color[0]);
			SetUniformFloat(uSpecularPower, pparams.m_specular_factor);
			SetUniformInt(uDiffuseMap, 0);
			SetUniformInt(uNormalMap, 1);		

			if (pparams.m_enable_wireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				ValidateOpenGL(L"Can't change polygon mode");
			}			
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				ValidateOpenGL(L"Can't change polygon mode");
			}
		}

		int64_t RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::GetRequiredAttributesSet() const 
		{
			return Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Tangent, VertexComponent::Bitangent, VertexComponent::Texture0>::Value();
		}

		void RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();

			glEnable(GL_DEPTH_TEST);
			//ValidateOpenGL(L"Unable to enable depth test");
			//glDepthFunc(GL_LESS);
			//ValidateOpenGL(L"Unable to set less depth function");
			//glDepthMask(GL_TRUE);
			//ValidateOpenGL(L"Unable to enable depth mask");
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//ValidateOpenGL(L"Unable to set polygon mode");
			/*glEnable(GL_BLEND);
			ValidateOpenGL(L"Unable to enable blend");
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			ValidateOpenGL(L"Unable to set blend func");
			glEnable(GL_CULL_FACE);
			ValidateOpenGL(L"Unable to enable cull facing");
			glCullFace(GL_FRONT);
			ValidateOpenGL(L"Unable to set cull face mode");*/
		}

		void RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader>::End()
		{
			OpenGLRenderContext::End();			

			//glEnable(GL_DEPTH_TEST);			
			//glDepthFunc(GL_LESS);
			//glDepthMask(GL_TRUE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
		}	
	}
}
