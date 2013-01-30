#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS

#include "gl_render_context.h"
#include "shaders/vertex/vs_grass.h"
#include "shaders/fragment/fs_grass.h"

namespace GPU
{
	namespace OpenGL
	{
		/**********************************************************************************************/
		/*			GRASS RENDER 3D
		/**********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjView;
			unsigned uHeightMap;
			unsigned uPosition;
			unsigned uTime;
			unsigned uWindStrength;
			unsigned uWindDirection;
			unsigned uDiffuseColor;
			unsigned uDiffuseMap;

		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderGrass);
				m_fragment_shader.reset(new FragmentShaderGrass);
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
				uProjView = GetUniformLocation("uProjView");
				uHeightMap = GetUniformLocation("uHeightMap");
				uPosition = GetUniformLocation("uPosition");
				uTime = GetUniformLocation("uTime");
				uWindStrength = GetUniformLocation("uWindStrength");
				uWindDirection = GetUniformLocation("uWindDirection");
				uDiffuseColor = GetUniformLocation("uDiffuseColor");
				uDiffuseMap = GetUniformLocation("uDiffuseMap");
			}

			void BindParameters(const CoreState& pparams)
			{	
				//const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
				//SetUniformMatrix4f(uProjView, &params.m_proj_view[0]);
				//SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);
				//SetUniformVector3f(uPosition, &params.m_position[0]);
				//SetUniformFloat(uTime, params.m_time);
				//SetUniformFloat(uWindStrength, params.m_wind_strength);
				//SetUniformVector3f(uWindDirection, &params.m_wind_direction[0]);
				//SetUniformInt(uDiffuseMap, 0);
				//SetUniformInt(uHeightMap, 1);	
			}

			VertexAttributes GetRequiredAttributesSet() const 
			{
				return COMPONENT_POSITION|COMPONENT_TEXTURE;
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

#endif