//#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_BUMP_MAPPING
//#define _H_PUNK_OPENGL_RENDER_CONTEXT_BUMP_MAPPING

//#ifdef USE_BUMP_MAPPING_RC

//#include "gl_render_context.h"
//#include "shaders/vertex/vs_bump.h"
//#include "shaders/fragment/fs_bump.h"

//namespace GPU
//{
//	namespace OpenGL
//	{
//        /**********************************************************************************************
//        *			BUMP MAPPING 3D
//        **********************************************************************************************/
//		template<> class RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader> : public OpenGLRenderContext
//		{
//			unsigned uWorld;
//			unsigned uView;
//			unsigned uProj;
//			unsigned uNormalMatrix;
//			unsigned uLightPosition;
//			unsigned uAmbient;
//			unsigned uSpecular;
//			unsigned uDiffuse;
//			unsigned uSpecularPower;
//			unsigned uDiffuseMap;
//			unsigned uNormalMap;

//		public:

//			RenderContextPolicy();
//			void Init() override;
//			void InitUniforms() override;
//			void BindParameters(const CoreState& pparams) override;
//			int64_t GetRequiredAttributesSet() const override;
//			virtual void Begin() override;
//			virtual void End() override;
//		};
//	}
//}

//#endif  //  USE_BUMP_MAPPING_RC
//#endif
