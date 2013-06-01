#ifdef USE_SKINNING_RC

#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING

#include "gl_render_context.h"
#include "shaders/vertex/vs_skinning.h"
#include "shaders/fragment/fs_skinning.h"

namespace GPU
{
	namespace OpenGL
	{
        /**********************************************************************************************
        *			SKINNING 3D
        **********************************************************************************************/
		template<> class RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> : public OpenGLRenderContext
		{	
		public:

			RenderContextPolicy();
			virtual ~RenderContextPolicy();

			void Init() override;
			void InitUniforms() override;
			void BindParameters(const CoreState& pparams) override;
			int64_t GetRequiredAttributesSet() const override;
			virtual void Begin() override;
			virtual void End() override;

		private:
			static const int MAX_BONES = 64;

			unsigned uWorld;
			unsigned uView;
			unsigned uProj;
			unsigned uMeshMatrix;
			unsigned uMeshMatrixInversed;
			unsigned uNormalMatrix;
			unsigned uProjViewWorld;
			unsigned uViewWorld;
			unsigned uLightPosition;
			unsigned uBones[64];
			unsigned uAmbient;
			unsigned uSpecular;
			unsigned uDiffuse;
			unsigned uSpecularPower;
			unsigned uDiffuseMap;
			unsigned uNormalMap;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING

#endif  //  USE_SKINNING_RC
