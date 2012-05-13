#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING
#define _H_PUNK_OPENGL_RENDER_CONTEXT_SKINNING

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
	class MODULE_OPENGL RenderContextSkinning : public RenderContext
	{
	public:

		RenderContextSkinning();
		RenderContextSkinning(const RenderContextSkinning& rc);
		RenderContextSkinning& operator = (const RenderContextSkinning& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetLightPosition(const Math::Vector3<float>& v);
		void SetAmbientColor(const Math::Vector4<float>& v);
		void SetSpecularColor(const Math::Vector4<float>& v);
		void SetDiffuseColor(const Math::Vector4<float>& m);
		void SetSpecularPower(float v);
		void SetBoneMatrix(int bone_id, const Math::Matrix4x4<float>& m);
	};
};

#endif