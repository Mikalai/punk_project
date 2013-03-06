#include "rc_terrain.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderTerrain);
			m_fragment_shader.reset(new FragmentShaderTerrain);
			Init();
		}

		void RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

		void RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::InitUniforms()
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

		void RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::BindParameters(const CoreState& pparams)
		{										
			Math::mat4 proj_view_world = pparams.m_projection * pparams.m_view * pparams.m_world;
			Math::mat3 normal_matrix = (pparams.m_view * pparams.m_world).Inversed().Transposed().RotationPart();

			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformMatrix4f(uWorld, &pparams.m_world[0]);
			SetUniformMatrix4f(uView, &pparams.m_view[0]);
			SetUniformMatrix4f(uProjection, &pparams.m_projection[0]);
			SetUniformMatrix3f(uNormalTransform, &normal_matrix[0]);
			SetUniformInt(uSlice, pparams.m_terrain_slices);

			if (!pparams.m_lights.empty())
				SetUniformVector3f(uLightDirection, &pparams.m_lights[0]->GetPosition().Normalized()[0]);
			else
			{
				Math::vec3 v(1,1,0);
				SetUniformVector3f(uLightDirection, &v.Normalized()[0]);
			}

			SetUniformVector4f(uDiffuseColor, &pparams.m_diffuse_color[0]);

			SetUniformVector2f(uPosition, &pparams.m_terran_position[0]);
			SetUniformInt(uHeightMapUniform, pparams.m_height_map_slot);
			SetUniformInt(uDiffuseMapUniform1, pparams.m_diffuse_slot_0);
			SetUniformInt(uDiffuseMapUniform2, pparams.m_diffuse_slot_1);
			SetUniformFloat(uLevel, float(pparams.m_terrain_level));
			SetUniformInt(ui, pparams.m_terrain_i);
			SetUniformInt(uj, pparams.m_terrain_j);
			SetUniformFloat(uScale, 1);		

			auto vv = pparams.m_world.TranslationPart();
			Math::vec2 v(floor(vv.X()), floor(vv.Y()));
			SetUniformVector2f(uTerrainPosition, &v[0]);
			//SetUniformVector2f(uPosition, &pparams.m_terran_position[0]);
			SetUniformVector2f(uPosition, &v[0]);

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

		VertexAttributes RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::GetRequiredAttributesSet() const 
		{
			return COMPONENT_POSITION|COMPONENT_TEXTURE|COMPONENT_NORMAL|COMPONENT_FLAG;
		}

		void RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

		void RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader>::End()
		{
			OpenGLRenderContext::End();			
		}	
	}
}