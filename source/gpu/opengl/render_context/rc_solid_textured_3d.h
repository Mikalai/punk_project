#ifndef _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D
#define _H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D

#include "gl_render_context.h"
#include "shaders/vertex/vs_transformed_textured_3d.h"
#include "shaders/fragment/fs_solid_textured.h"

namespace GPU
{
	namespace OpenGL
	{

		template<> class RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;
			unsigned uDiffuseMap;
			unsigned uTextureMatrix;

		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderTransformTextured3D);
				m_fragment_shader.reset(new FragmentShaderSolidTextured);
				Init();
			}

			virtual ~RenderContextPolicy()
			{
			}

			virtual void Init()
			{
				if (m_was_modified || !m_program)
				{
					OpenGLRenderContext::Init();
					InitUniforms();
				}
			}

			virtual void InitUniforms()
			{
				uProjViewWorld = GetUniformLocation("uProjViewWorld");
				uDiffuseColor = GetUniformLocation("uDiffuseColor");
				uDiffuseMap = GetUniformLocation("uDiffuseMap");
				uTextureMatrix = GetUniformLocation("uTextureMatrix");
			}

			virtual void BindParameters(const CoreState& params)
			{									
				const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_local;
				SetUniformMatrix4f(uProjViewWorld, &(proj_view_world[0]));
				SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));
				SetUniformInt(uDiffuseMap, params.m_diffuse_slot_0);
				SetUniformMatrix2f(uTextureMatrix, &params.m_texture_matrix[0]);
			}

			virtual VertexAttributes GetRequiredAttributesSet() const 
			{
				return COMPONENT_POSITION|COMPONENT_TEXTURE;
			}

			virtual void Begin()
			{
				/*
				Begin();
				BindParameters()
				***
				render();
				***
				BindParameters()
				render();
				End();
				*/

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

#endif	//	_H_PUNK_OPENGL_RC_SOLID_TEXTURED_3D