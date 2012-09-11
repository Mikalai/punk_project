#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_COLOR_3D

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Vector4;
}

namespace OpenGL
{
	class PUNK_ENGINE RenderContextSolid3D : public RenderContext
	{
	public:
		RenderContextSolid3D();
		RenderContextSolid3D(const RenderContextSolid3D& rc);
		RenderContextSolid3D& operator = (const RenderContextSolid3D& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetDiffuseColor(const Math::Vector4<float>& m);
	};
};

#endif