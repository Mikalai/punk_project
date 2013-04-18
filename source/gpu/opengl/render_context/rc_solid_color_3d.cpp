#include "rc_solid_color_3d.h"
#include "gl_render_context.h"
#include "shaders/vertex/vs_solid_color.h"
#include "shaders/fragment/fs_solid_color.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderSolid);
			m_fragment_shader.reset(new FragmentShaderSolid);
			Init();
		}

		RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::~RenderContextPolicy()
		{
		}

		void RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

		void RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
		}

		void RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::BindParameters(const CoreState& params)
		{			
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));

			if (params.m_enable_wireframe)
			{
				glLineWidth(params.m_line_width);
				ValidateOpenGL(L"Can't line width");
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				ValidateOpenGL(L"Can't change polygon mode");
			}			
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				ValidateOpenGL(L"Can't change polygon mode");
			}

			if (params.m_depth_test)
			{
				glEnable(GL_DEPTH_TEST);
				ValidateOpenGL(L"Can't enable depth test");
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				ValidateOpenGL(L"Can't disable depth test");
			}
		}

		int64_t RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::GetRequiredAttributesSet() const 
		{
			return Vertex<VertexComponent::Position>::Value();
		}

		void RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

		void RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader>::End()
		{
			OpenGLRenderContext::End();			
		}		
	}
}