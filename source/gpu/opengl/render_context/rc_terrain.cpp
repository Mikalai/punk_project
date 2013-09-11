#ifdef USE_TERRAIN_RC

#include "rc_terrain.h"

namespace Gpu
{
	namespace OpenGL
	{
        RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderTerrain);
			m_fragment_shader.reset(new FragmentShaderTerrain);
			Init();
		}

        void RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

        void RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::InitUniforms()
		{
			uTextureMatrix = GetUniformLocation("uTextureMatrix");
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProjection = GetUniformLocation("uProjection");
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uNormalTransform = GetUniformLocation("uNormalTransform");
			uHeightMapUniform = GetUniformLocation("uHeightMapUniform");
			uScale = GetUniformLocation("uScale");
			uNormalMapUniform = GetUniformLocation("uNormalMapUniform");
			uDiffuseMapUniform1 = GetUniformLocation("uDiffuseMapUniform1");
			uDiffuseMapUniform2 = GetUniformLocation("uDiffuseMapUniform2");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uLightDirection = GetUniformLocation("uLightDirection");
			uViewSize = GetUniformLocation("uViewSize");
		}

        void RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::BindParameters(const CoreState& pparams)
		{										
			Math::mat4 proj_view_world = pparams.m_projection * pparams.m_view * pparams.m_world;
			Math::mat3 normal_matrix = (pparams.m_view * pparams.m_world).Inversed().Transposed().RotationPart();

			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformMatrix4f(uWorld, &pparams.m_world[0]);
			SetUniformMatrix4f(uView, &pparams.m_view[0]);
			SetUniformMatrix4f(uProjection, &pparams.m_projection[0]);
			SetUniformMatrix3f(uNormalTransform, &normal_matrix[0]);

			if (!pparams.m_lights.empty())
			{
				Math::vec3 v(0,1,1);
				SetUniformVector3f(uLightDirection, &v.Normalized()[0]);
				//SetUniformVector3f(uLightDirection, &pparams.m_lights[0]->GetPosition().Normalized()[0]);
			}			
			else
			{
				Math::vec3 v(1,1,0);
				SetUniformVector3f(uLightDirection, &v.Normalized()[0]);
			}

			SetUniformVector4f(uDiffuseColor, &pparams.m_diffuse_color[0]);


			SetUniformMatrix4f(uTextureMatrix, &pparams.m_texture_matrix[0]);
			SetUniformInt(uHeightMapUniform, 2);
			SetUniformInt(uDiffuseMapUniform1, 0);
			SetUniformInt(uDiffuseMapUniform2, 1);
			SetUniformFloat(uScale, 1);		

			SetUpOpenGL(params);
		}

        int64_t RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::GetRequiredAttributesSet() const
		{
			return Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0, VertexComponent::Flag>::Value();
		}

        void RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

        void RenderContextPolicy<TerrainVertexShader, TerrainFragmentShader, TerrainGeometryShader>::End()
		{
			OpenGLRenderContext::End();			
		}	
	}
}

#endif  //  USE_TERRAIN_RC
