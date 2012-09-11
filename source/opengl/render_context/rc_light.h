#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_LIGHT
#define _H_PUNK_OPENGL_RENDER_CONTEXT_LIGHT

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Matrix3x3;
	template<class T> class Vector4;
	template<class T> class Vector3;
}

namespace OpenGL
{
	class PUNK_ENGINE RenderContextLight : public RenderContext
	{
	public:
		RenderContextLight();
		RenderContextLight(const RenderContextLight& rc);
		RenderContextLight& operator = (const RenderContextLight& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetLightPosition(const Math::Vector3<float>& v);
		void SetAmbientColor(const Math::Vector4<float>& v);
		void SetSpecularColor(const Math::Vector4<float>& v);
		void SetDiffuseColor(const Math::Vector4<float>& m);
		void SetSpecularPower(float v);
	};
};

#endif