#ifndef _H_PUNK_OPENGL_RC_TERRAIN
#define _H_PUNK_OPENGL_RC_TERRAIN

#include "gl_render_context.h"
#include "shaders/vertex/vs_terrain.h"
#include "shaders/fragment/fs_terrain.h"

namespace GPU
{
	namespace OpenGL
	{
		/**********************************************************************************************/
		/*			TERRAIN RENDER 3D
		/**********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> : public OpenGLRenderContext
		{	
		public:

			RenderContextPolicy();
			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& pparams) override;
			int64_t GetRequiredAttributesSet() const override;
			void Begin() override;
			void End() override;

		private:
			
			unsigned uTextureMatrix;
			unsigned uWorld;
			unsigned uView;
			unsigned uProjection;
			unsigned uProjViewWorld;
			unsigned uNormalTransform;
			unsigned ui;
			unsigned uj;
			unsigned uViewSize;
			unsigned uHeightMapUniform;
			unsigned uScale;
			unsigned uPosition;
			unsigned uLevel;
			unsigned uNormalMapUniform;
			unsigned uDiffuseMapUniform1;
			unsigned uDiffuseMapUniform2;
			unsigned uDiffuseColor;
			unsigned uLightDirection;
			unsigned uTerrainPosition;
			unsigned uSlice;
		};
	}
}
#endif	//	_H_PUNK_OPENGL_RC_TERRAIN