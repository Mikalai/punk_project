#ifndef _H_PUNK_OPENGL_RC_TERRAIN
#define _H_PUNK_OPENGL_RC_TERRAIN

#include "gl_render_context.h"
#include "shaders/vertex/vs_terrain.h"
#include "shaders/fragment/fs_terrain.h"

namespace GPU
{
	namespace OpenGL
	{
		/**********************************************************************************************/
		/*			TERRAIN RENDER 3D
		/**********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> : public OpenGLRenderContext
		{	
			unsigned uWorld;
			unsigned uView;
			unsigned uProjection;
			unsigned uProjViewWorld;
			unsigned uNormalTransform;
			unsigned ui;
			unsigned uj;
			unsigned uViewSize;
			unsigned uHeightMapUniform;
			unsigned uScale;
			unsigned uPosition;
			unsigned uLevel;
			unsigned uNormalMapUniform;
			unsigned uDiffuseMapUniform1;
			unsigned uDiffuseMapUniform2;
			unsigned uDiffuseColor;
			unsigned uLightDirection;
			unsigned uTerrainPosition;
			unsigned uSlice;
		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderTerrain);
				m_fragment_shader.reset(new FragmentShaderTerrain);
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
				uProjection = GetUniformLocation("uProjection");
				uProjViewWorld = GetUniformLocation("uProjViewWorld");
				uNormalTransform = GetUniformLocation("uNormalTransform");
				ui = GetUniformLocation("ui");
				uj = GetUniformLocation("uj");
				uHeightMapUniform = GetUniformLocation("uHeightMapUniform");
				uScale = GetUniformLocation("uScale");
				uPosition = GetUniformLocation("uPosition");
				uLevel = GetUniformLocation("uLevel");
				uNormalMapUniform = GetUniformLocation("uNormalMapUniform");
				uDiffuseMapUniform1 = GetUniformLocation("uDiffuseMapUniform1");
				uDiffuseMapUniform2 = GetUniformLocation("uDiffuseMapUniform2");
				uDiffuseColor = GetUniformLocation("uDiffuseColor");
				uLightDirection = GetUniformLocation("uLightDirection");
				uViewSize = GetUniformLocation("uViewSize");
				uTerrainPosition = GetUniformLocation("uTerrainPosition");
				uSlice = GetUniformLocation("uSlice");
			}

			void BindParameters(const CoreState& pparams)
			{										
				Math::mat4 proj_view_world = pparams.m_camera->GetProjectionMatrix() * pparams.m_camera->GetViewMatrix() * pparams.m_local;
				Math::mat3 normal_matrix = (pparams.m_camera->GetViewMatrix() * pparams.m_local).Inversed().Transposed().RotationPart();

				SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
				SetUniformMatrix4f(uWorld, &pparams.m_local[0]);
				SetUniformMatrix4f(uView, &pparams.m_camera->GetViewMatrix()[0]);
				SetUniformMatrix4f(uProjection, &pparams.m_camera->GetProjectionMatrix()[0]);
				SetUniformMatrix3f(uNormalTransform, &normal_matrix[0]);
				SetUniformInt(uSlice, pparams.m_terrain_slices);

				if (!pparams.m_lights.empty())
					SetUniformVector3f(uLightDirection, &pparams.m_lights[0]->GetPosition().Normalized()[0]);
				else
				{
					Math::vec3 v(1,1,0);
					SetUniformVector3f(uLightDirection, &v.Normalized()[0]);
				}

				if (pparams.m_material.IsValid())
					SetUniformVector4f(uDiffuseColor, &pparams.m_material->GetDiffuseColor()[0]);
				else
				{
					Math::vec4 v(1,1,1,1);
					SetUniformVector4f(uDiffuseColor, &v[0]);
				}
				SetUniformVector2f(uPosition, &pparams.m_terran_position[0]);
				SetUniformInt(uHeightMapUniform, pparams.m_height_map_slot);
				SetUniformInt(uDiffuseMapUniform1, pparams.m_diffuse_slot_0);
				SetUniformInt(uDiffuseMapUniform2, pparams.m_diffuse_slot_1);
				SetUniformFloat(uLevel, float(pparams.m_terrain_level));
				SetUniformInt(ui, pparams.m_terrain_i);
				SetUniformInt(uj, pparams.m_terrain_j);
				SetUniformInt(uViewSize, pparams.m_terrain_observer->GetTerrainView()->GetViewSize());
				SetUniformFloat(uScale, pparams.m_terrain->GetHeightScale());			
				SetUniformVector2f(uTerrainPosition, &pparams.m_terrain_observer->GetTerrainView()->GetPosition()[0]);

				if (pparams.m_wireframe)
				{
					glLineWidth(pparams.m_line_width);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					CHECK_GL_ERROR(L"Can't change polygon mode");
				}			
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					CHECK_GL_ERROR(L"Can't change polygon mode");
				}

				if (pparams.m_depth_test)
				{
					glEnable(GL_DEPTH_TEST);
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
				}
			}

			VertexAttributes GetRequiredAttributesSet() const 
			{
				return COMPONENT_POSITION|COMPONENT_TEXTURE|COMPONENT_NORMAL|COMPONENT_FLAG;
			}

			virtual void Begin()
			{
				Init();
				OpenGLRenderContext::Begin();
			}

			virtual void End()
			{
				OpenGLRenderContext::End();			
			}	
		};
	}
}
#endif	//	_H_PUNK_OPENGL_RC_TERRAIN