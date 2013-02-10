#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D

#include "gl_render_context.h"
#include "shaders/vertex/vs_solid_color.h"
#include "shaders/fragment/fs_solid_color.h"

namespace GPU
{
	namespace OpenGL
	{
		template<> class RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;

		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderSolid);
				m_fragment_shader.reset(new FragmentShaderSolid);
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
			}

			virtual void BindParameters(const CoreState& params)
			{			
				const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_local;
				SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
				SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));

				if (params.m_wireframe)
				{
					glLineWidth(params.m_line_width);
					CHECK_GL_ERROR(L"Can't line width");
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					CHECK_GL_ERROR(L"Can't change polygon mode");
				}			
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					CHECK_GL_ERROR(L"Can't change polygon mode");
				}
			}

			virtual VertexAttributes GetRequiredAttributesSet() const 
			{
				return COMPONENT_POSITION;
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