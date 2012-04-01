#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_TEXTURED_3D
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SOLID_TEXTURED_3D

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Vector4;
}

namespace OpenGL
{
	class MODULE_OPENGL RenderContextTextured3D : public RenderContext
	{
	public:
		RenderContextTextured3D();
		RenderContextTextured3D(const RenderContextTextured3D& rc);
		RenderContextTextured3D& operator = (const RenderContextTextured3D& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetDiffuseColor(const Math::Vector4<float>& m);		
	};
};

#endif