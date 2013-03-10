#include "rc_skinning.h"

namespace GPU
{
	namespace OpenGL
	{

		RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderSkinning);
			m_fragment_shader.reset(new FragmentShaderSkinning);
			Init();
		}

		RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::~RenderContextPolicy()
		{
		}

		void RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}			
		}

		void RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProj = GetUniformLocation("uProj");
			uMeshMatrix = GetUniformLocation("uMeshMatrix");
			uMeshMatrixInversed = GetUniformLocation("uMeshMatrixInversed");
			uNormalMatrix = GetUniformLocation("uNormalMatrix");
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uViewWorld = GetUniformLocation("uViewWorld");
			uLightPosition = GetUniformLocation("uLightPosition");
			for (int i = 0; i < MAX_BONES; ++i)
			{
				char buf[128];
				sprintf_s<128>(buf, "uBones[%d]", i);
				uBones[i] = GetUniformLocation(buf);
			}
			uAmbient = GetUniformLocation("uAmbient");
			uSpecular = GetUniformLocation("uSpecular");
			uDiffuse = GetUniformLocation("uDiffuse");
			uSpecularPower = GetUniformLocation("uSpecularPower");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uNormalMap = GetUniformLocation("uNormalMap");
		}

		void RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::BindParameters(const CoreState& pparams)
		{							
			Math::mat4 mesh_matrix = Math::mat4::CreateIdentity();
			Math::mat4 view_world = pparams.m_view * pparams.m_world;
			Math::mat4 proj_view_world = pparams.m_projection * pparams.m_view * pparams.m_world;
			Math::mat3 normal_matrix = (pparams.m_view * pparams.m_world).Inversed().Transposed().RotationPart();
			SetUniformMatrix4f(uWorld, &pparams.m_world[0]);			
			SetUniformMatrix4f(uView, &pparams.m_view[0]);			
			SetUniformMatrix4f(uProj, &pparams.m_projection[0]);			
			SetUniformMatrix4f(uMeshMatrix, &mesh_matrix[0]);//pparams.m_mesh_matrix[0]);
			SetUniformMatrix4f(uMeshMatrixInversed, &mesh_matrix[0]);//pparams.m_mesh_matrix.Inversed()[0]);
			SetUniformMatrix3f(uNormalMatrix, &normal_matrix[0]);

			if (!pparams.m_lights.empty())
				SetUniformVector3f(uLightPosition, &pparams.m_lights[0]->GetPosition()[0]);
			else
			{
				Math::vec3 v(0,0,0);
				SetUniformVector3f(uLightPosition, &v[0]);
			}

			SetUniformVector4f(uAmbient, &(Math::vec4(pparams.m_ambient_color)[0]));
			SetUniformVector4f(uSpecular, &pparams.m_specular_color[0]);
			SetUniformVector4f(uDiffuse, &pparams.m_diffuse_color[0]);
			SetUniformFloat(uSpecularPower, pparams.m_specular_factor);
			SetUniformInt(uDiffuseMap, 0);
			SetUniformInt(uNormalMap, 1);				
			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformMatrix4f(uViewWorld, &view_world[0]);
			for (int i = 0; i < _countof(pparams.m_bone_matrix); ++i)
			{
				SetUniformMatrix4f(uBones[i], &(pparams.m_bone_matrix[i] * pparams.m_local)[0]);
			}
		}

		VertexAttributes RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::GetRequiredAttributesSet() const 
		{
			return COMPONENT_POSITION|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_NORMAL|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID;
		}

		void RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();

			glEnable(GL_DEPTH_TEST);
			CHECK_GL_ERROR(L"Unable to enable depth test");
			glDepthFunc(GL_LESS);
			CHECK_GL_ERROR(L"Unable to set less depth function");
			glDepthMask(GL_TRUE);
			CHECK_GL_ERROR(L"Unable to enable depth mask");
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			CHECK_GL_ERROR(L"Unable to set polygon mode");
			/*glEnable(GL_BLEND);
			CHECK_GL_ERROR(L"Unable to enable blend");
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			CHECK_GL_ERROR(L"Unable to set blend func");
			glEnable(GL_CULL_FACE);
			CHECK_GL_ERROR(L"Unable to enable cull facing");
			glCullFace(GL_FRONT);
			CHECK_GL_ERROR(L"Unable to set cull face mode");*/
		}

		void RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader>::End()
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