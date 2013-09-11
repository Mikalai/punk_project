#ifdef USE_PAINTER_RC
#include "rc_painter.h"

namespace Gpu
{
	namespace OpenGL
	{
        /**********************************************************************************************
        *			PAINTER RENDER
        **********************************************************************************************/
		RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderPainter);
			m_fragment_shader.reset(new FragmentShaderPainter);
			Init();
		}

		void RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

		void RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uTextureMatrix = GetUniformLocation("uTextureMatrix");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uTextColor = GetUniformLocation("uTextColor");
			uUseTexture = GetUniformLocation("uUseTexture");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uTextMap = GetUniformLocation("uTextMap");			
		}

		void RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::BindParameters(const CoreState& pparams)
		{									
			Math::mat4 proj_view_world = pparams.m_projection * pparams.m_view * pparams.m_local;
			SetUniformMatrix4f(uWorld, &pparams.m_local[0]);
			SetUniformMatrix2f(uTextureMatrix, &pparams.m_texture_matrix[0]);
			SetUniformVector4f(uDiffuseColor, &pparams.m_diffuse_color[0]);
			SetUniformVector4f(uTextColor, &pparams.m_text_color[0]);
			Math::vec4 use_texture;
			use_texture.Y() = pparams.m_use_diffuse_texture ? 1.0f : 0.0f;
			use_texture.X() = pparams.m_use_text_texture ? 1.0f : 0.0f; 
			SetUniformVector4f(uUseTexture, &use_texture[0]);
			
			if (pparams.m_use_diffuse_texture)
				SetUniformInt(uDiffuseMap, pparams.m_diffuse_slot_0);
			
			if (pparams.m_use_text_texture)
				SetUniformInt(uTextMap, pparams.m_text_slot);

			glLineWidth(pparams.m_line_width);

			if (pparams.m_enable_wireframe)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				ValidateOpenGL(L"Can't change polygon mode");
			}			
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				ValidateOpenGL(L"Can't change polygon mode");
			}

			if (pparams.m_blending)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}

		int64_t RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::GetRequiredAttributesSet() const 
		{
			return Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value();
		}

		void RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

		void RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader>::End()
		{
			OpenGLRenderContext::End();			
		}		
	};
}
#endif  //  USE_PAINTER_RC
