#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_GUI
#define _H_PUNK_OPENGL_RENDER_CONTEXT_GUI

#include "render_context.h"

namespace Math
{
	template<class T> class Matrix4x4;
	template<class T> class Vector4;
}

namespace OpenGL
{
	class MODULE_OPENGL RenderContextGUI : public RenderContext
	{
	public:
		RenderContextGUI();
		RenderContextGUI(const RenderContextGUI& rc);
		RenderContextGUI& operator = (const RenderContextGUI& rc);

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m);
		void SetViewMatrix(const Math::Matrix4x4<float>& m);
		void SetWorldMatrix(const Math::Matrix4x4<float>& m);
		void SetDiffuseColor(const Math::Vector4<float>& m);		
	};
};

#endif