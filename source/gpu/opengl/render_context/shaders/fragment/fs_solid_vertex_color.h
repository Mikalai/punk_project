#ifndef _H_PUNK_OPENGL_SHADER_SOLID_VERTEX_COLOR
#define _H_PUNK_OPENGL_SHADER_SOLID_VERTEX_COLOR

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
		class FsSolidVertexColor : public Shader
		{
		public:
			FsSolidVertexColor();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;
		private:

		};
	}
}

#endif
