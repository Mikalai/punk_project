#ifdef USE_GUI_RC

#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GUI
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GUI

#include "gl_render_context.h"
#include "shaders/vertex/vs_gui.h"
#include "shaders/fragment/fs_gui.h"

namespace Gpu
{
	namespace OpenGL
	{
        /**********************************************************************************************
        *			GUI RENDER 2D
        **********************************************************************************************/
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

			RenderContextPolicy();
			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& pparams) override;
			int64_t GetRequiredAttributesSet() const= 0;
			void Begin() override;
			void End() override;
		};
	}
}
#endif

#endif  //  USE_GUI_RC
