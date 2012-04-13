#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_TERRAIN
#define _H_PUNK_OPENGL_RENDER_CONTEXT_TERRAIN

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Matrix3x3;
	template<class T> class Vector4;
	template<class T> class Vector3;
	template<class T> class Vector2;
}

namespace OpenGL
{
	class Texture2D;

	class MODULE_OPENGL RenderContextTerrain : public RenderContext
	{
	public:
		RenderContextTerrain();
		RenderContextTerrain(const RenderContextTerrain& rc);
		RenderContextTerrain& operator = (const RenderContextTerrain& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetDiffuseColor(const Math::Vector4<float>& m);
		void SetNormalTransform(const Math::Matrix3x3<float>& m);
		void SetPosition(const Math::Vector2<float>& v);
		void SetLevel(float level);
		void SetI(int i);
		void SetJ(int j);
		void SetLightDirection(const Math::Vector3<float>& v);
	};
};

#endif