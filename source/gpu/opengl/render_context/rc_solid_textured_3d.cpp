#include "rc_solid_textured_3d.h"

namespace GPU
{
	namespace OpenGL
	{

		RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderTransformTextured3D);
			m_fragment_shader.reset(new FragmentShaderSolidTextured);
			Init();
		}

		RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::~RenderContextPolicy()
		{
		}

		void RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

		void RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uTextureMatrix = GetUniformLocation("uTextureMatrix");
		}

		void RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::BindParameters(const CoreState& params)
		{									
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &(proj_view_world[0]));
			SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));
			SetUniformInt(uDiffuseMap, 0);
			SetUniformMatrix4f(uTextureMatrix, &params.m_texture_matrix[0]);

			if (params.m_enable_wireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				CHECK_GL_ERROR(L"Can't change polygon mode");
			}			
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				CHECK_GL_ERROR(L"Can't change polygon mode");
			}

			if (params.m_depth_test)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}

		VertexAttributes RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::GetRequiredAttributesSet() const 
		{
			return COMPONENT_POSITION|COMPONENT_TEXTURE;
		}

		void RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::Begin()
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

		void RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader>::End()
		{
			OpenGLRenderContext::End();			
		}		
	}
}
