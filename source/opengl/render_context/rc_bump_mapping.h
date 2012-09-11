#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_BUMP_MAPPING
#define _H_PUNK_OPENGL_RENDER_CONTEXT_BUMP_MAPPING

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
	class PUNK_ENGINE RenderContextBumpMapping : public RenderContext
	{
	public:
		RenderContextBumpMapping();
		RenderContextBumpMapping(const RenderContextBumpMapping& rc);
		RenderContextBumpMapping& operator = (const RenderContextBumpMapping& rc);

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