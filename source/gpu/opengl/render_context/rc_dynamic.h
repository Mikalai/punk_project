#ifndef RC_DYNAMIC_H
#define RC_DYNAMIC_H

#include "gl_render_context.h"

namespace Gpu
{
	namespace OpenGL
	{
		class DynamicRenderContext : public OpenGLRenderContext
		{
		public:
			DynamicRenderContext();

			void SetShaders(Shader* vs, Shader* fs, Shader* gs);
			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:

		};
	}
}

#endif // RC_DYNAMIC_H
