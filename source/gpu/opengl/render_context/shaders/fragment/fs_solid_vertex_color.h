#ifndef _H_PUNK_OPENGL_SHADER_SOLID_VERTEX_COLOR
#define _H_PUNK_OPENGL_SHADER_SOLID_VERTEX_COLOR

#include "..\shader.h"

namespace GPU
{
	namespace OpenGL
	{
		class FragmentShaderSolidVertexColor : public Shader
		{
		public:
			FragmentShaderSolidVertexColor();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;
		private:

		};
	}
}

#endif
