#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GRASS

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Vector4;
	template<class T> class Vector3;
}

namespace OpenGL
{
	class MODULE_OPENGL RenderContextGrass : public RenderContext
	{
	public:
		RenderContextGrass();
		RenderContextGrass(const RenderContextGrass& rc);
		RenderContextGrass& operator = (const RenderContextGrass& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetPosition(const Math::Vector3<float>& p);
		void SetDiffuseColor(const Math::Vector4<float>& m);	
		void SetTime(float time);
		void SetWindStrength(float value);
		void SetWindDirection(const Math::Vector3<float>& value);
	};
};

#endif