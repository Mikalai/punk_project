#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GUI
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GUI

#include "gl_render_context.h"
#include "shaders/vertex/vs_gui.h"
#include "shaders/fragment/fs_gui.h"

namespace GPU
{
	namespace OpenGL
	{
		/**********************************************************************************************/
		/*			GUI RENDER 2D
		/**********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderGUI, FragmentShaderGUI, NoShader> : public OpenGLRenderContext
		{	
			unsigned uProjViewWorld;
			unsigned uDiffuseColor;
			unsigned uTextureMatrix;
			unsigned uTextColor;
			unsigned uNoDiffuseTexture;
			unsigned uDiffuseMap;
			unsigned uTextMap;

		public:

			RenderContextPolicy()
			{
				m_vertex_shader.reset(new VertexShaderGUI);
				m_fragment_shader.reset(new FragmentShaderGUI);
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
				uProjViewWorld = GetUniformLocation("uProjViewWorld");
				uDiffuseColor = GetUniformLocation("uDiffuseColor");
				uTextColor = GetUniformLocation("uTextColor");
				uNoDiffuseTexture = GetUniformLocation("uNoDiffuseTexture");
				uDiffuseMap = GetUniformLocation("uDiffuseMap");
				uTextMap = GetUniformLocation("uTextMap");
				uTextureMatrix = GetUniformLocation("uTextureMatrix");
			}

			void BindParameters(const CoreState& pparams)
			{									
				Math::mat4 proj_view_world = pparams.m_projection * pparams.m_view * pparams.m_local;
				SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
				SetUniformMatrix2f(uTextureMatrix, &pparams.m_texture_matrix[0]);
				SetUniformVector4f(uDiffuseColor, &pparams.m_diffuse_color[0]);
				SetUniformVector4f(uTextColor, &pparams.m_text_color[0]);
				SetUniformVector4f(uNoDiffuseTexture, &pparams.m_no_diffuse_texture_color[0]);
				SetUniformInt(uDiffuseMap, pparams.m_diffuse_slot_0);
				SetUniformInt(uTextMap, pparams.m_text_slot);
				if (pparams.m_enable_wireframe)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					CHECK_GL_ERROR(L"Can't change polygon mode");
				}			
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					CHECK_GL_ERROR(L"Can't change polygon mode");
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