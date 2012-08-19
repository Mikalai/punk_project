#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_PARTICLE_SYSTEM
#define _H_PUNK_OPENGL_RENDER_CONTEXT_PARTICLE_SYSTEM

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
	class MODULE_OPENGL RenderContextParticle : public RenderContext
	{
	public:

		RenderContextParticle();
		RenderContextParticle(const RenderContextParticle& rc);
		RenderContextParticle& operator = (const RenderContextParticle& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);		
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);		
		void UseGravity(bool use);
		void SetTime(float time);
	};
};

#endif