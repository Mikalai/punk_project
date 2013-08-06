#ifndef VS_SOLID_VERTEX_COLOR_H
#define VS_SOLID_VERTEX_COLOR_H

#include "../shader.h"

namespace Gpu
{
	namespace OpenGL
	{
		class VsSolidVertexColor : public Shader
		{
		public:
			VsSolidVertexColor();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
			unsigned uProjViewWorld;
		};
	}
}


#endif // VS_SOLID_VERTEX_COLOR_H
