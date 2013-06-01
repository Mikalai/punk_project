#ifdef USE_GRASS_RC

#include "rc_grass.h"

#include "gl_render_context.h"
#include "shaders/vertex/vs_grass.h"
#include "shaders/fragment/fs_grass.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderGrass);
			m_fragment_shader.reset(new FragmentShaderGrass);
			Init();
		}

		void RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

		void RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::InitUniforms()
		{
			uProjView = GetUniformLocation("uProjView");
			uHeightMap = GetUniformLocation("uHeightMap");
			uPosition = GetUniformLocation("uPosition");
			uTime = GetUniformLocation("uTime");
			uWindStrength = GetUniformLocation("uWindStrength");
			uWindDirection = GetUniformLocation("uWindDirection");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
		}

		void RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::BindParameters(const CoreState& pparams)
		{	
			//const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			//SetUniformMatrix4f(uProjView, &params.m_proj_view[0]);
			//SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);
			//SetUniformVector3f(uPosition, &params.m_position[0]);
			//SetUniformFloat(uTime, params.m_time);
			//SetUniformFloat(uWindStrength, params.m_wind_strength);
			//SetUniformVector3f(uWindDirection, &params.m_wind_direction[0]);
			//SetUniformInt(uDiffuseMap, 0);
			//SetUniformInt(uHeightMap, 1);	
		}

		int64_t RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::GetRequiredAttributesSet() const 
		{
			return Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value();
		}

		void RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

		void RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader>::End()
		{
			OpenGLRenderContext::End();			
		}			
	}
}

#endif  //  USE_GRASS_RC
