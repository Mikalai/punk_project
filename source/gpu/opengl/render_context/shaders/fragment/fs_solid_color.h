#ifndef _H_PUNK_OPENGL_SHADER_SOLID_COLOR
#define _H_PUNK_OPENGL_SHADER_SOLID_COLOR

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
		class FsSolid : public Shader
		{
		public:
			FsSolid();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;
		private:
			unsigned uDiffuseColor;
		};
	}
}

#endif
