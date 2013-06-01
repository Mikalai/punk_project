#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D
#define _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D

#include "..\shader.h"

namespace GPU
{
	namespace OpenGL
	{
		class VertexShaderSolid : public Shader
		{
		public:
			VertexShaderSolid();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;

		private:
			unsigned uProjViewWorld;
		};
	}
}

#endif
