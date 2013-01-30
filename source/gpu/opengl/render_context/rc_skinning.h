#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING

#include "gl_render_context.h"
#include "shaders/vertex/vs_skinning.h"
#include "shaders/fragment/fs_skinning.h"

namespace GPU
{
	namespace OpenGL
	{
		/**********************************************************************************************/
		/*			SKINNING 3D
		/**********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> : public OpenGLRenderContext
		{	
			static const int MAX_BONES = 64;

			unsigned uWorld;
			unsigned uView;
			unsigned uProj;
			unsigned uMeshMatrix;
			unsigned uMeshMatrixInversed;
			unsigned uNormalMatrix;
			unsigned uProjViewWorld;
			unsigned uViewWorld;
			unsigned uLightPosition;
			unsigned uBones[64];
			unsigned uAmbient;
			unsigned uSpecular;
			unsigned uDiffuse;
			unsigned uSpecularPower;
			unsigned uDiffuseMap;
			unsigned uNormalMap;

		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderSkinning);
				m_fragment_shader.reset(new FragmentShaderSkinning);
				Init();
			}

			void Init()
			{
				if (m_was_modified || !m_program)
				{
					OpenGLRenderContext::Init();
					InitUniforms();
				}			
			}

			void InitUniforms()
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

			void BindParameters(const CoreState& pparams)
			{							
				Math::mat4 mesh_matrix = Math::mat4::CreateIdentity();
				Math::mat4 view_world = pparams.m_camera->GetViewMatrix() * pparams.m_local;
				Math::mat4 proj_view_world = pparams.m_camera->GetProjectionMatrix() * pparams.m_camera->GetViewMatrix() * pparams.m_local;
				Math::mat3 normal_matrix = (pparams.m_camera->GetViewMatrix() * pparams.m_local).Inversed().Transposed().RotationPart();
				SetUniformMatrix4f(uWorld, &pparams.m_armature_world[0]);			
				SetUniformMatrix4f(uView, &pparams.m_camera->GetViewMatrix()[0]);			
				SetUniformMatrix4f(uProj, &pparams.m_camera->GetProjectionMatrix()[0]);			
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
				SetUniformVector4f(uAmbient, &(Math::vec4(pparams.m_material->GetAmbient()))[0]);
				SetUniformVector4f(uSpecular, &pparams.m_material->GetSpecularColor()[0]);
				SetUniformVector4f(uDiffuse, &pparams.m_material->GetDiffuseColor()[0]);
				SetUniformFloat(uSpecularPower, pparams.m_material->GetSpecularFactor());
				SetUniformInt(uDiffuseMap, pparams.m_diffuse_slot_0);
				SetUniformInt(uNormalMap, pparams.m_normal_slot);				
				SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
				SetUniformMatrix4f(uViewWorld, &view_world[0]);
				for (int i = 0; i < pparams.m_armature->GetBonesCount(); ++i)
				{
					const Virtual::Bone* bone = pparams.m_armature->GetBoneByIndex(i);
					Math::mat4 m;
					//out_message() << bone->GetName() << ": " << bone->GetAnimatedGlobalMatrix().ToString() << std::endl;
					//SetUniformMatrix4f(uBones[i], &(m[0]));
					//SetUniformMatrix4f(uBones[i], &(bone->GetAnimatedGlobalMatrix())[0]);
					SetUniformMatrix4f(uBones[i], &(/*pparams.m_mesh_matrix_local.Inversed() **/ bone->GetAnimatedGlobalMatrix() * pparams.m_mesh_matrix_local)[0]);
				}
			}

			VertexAttributes GetRequiredAttributesSet() const 
			{
				return COMPONENT_POSITION|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_NORMAL|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID;
			}

			virtual void Begin()
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

			virtual void End()
			{
				OpenGLRenderContext::End();			

				//glEnable(GL_DEPTH_TEST);			
				//glDepthFunc(GL_LESS);
				//glDepthMask(GL_TRUE);
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
			}	
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING