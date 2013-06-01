#ifndef _H_PUNK_OPENGL_FRAGMENT_PER_VERTEX_LIGHTING_DIFFUSE
#define _H_PUNK_OPENGL_FRAGMENT_PER_VERTEX_LIGHTING_DIFFUSE

#include "..\shader.h"

namespace GPU
{
	namespace OpenGL
	{
        class FsPerVertexLightingDiffuse : public Shader
		{
		public:
            FsPerVertexLightingDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uDiffuseColor;
		};
	}
}

#endif
