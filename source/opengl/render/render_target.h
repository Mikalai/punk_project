#ifndef _H_PUNK_OPENGL_RENDER_TARGET
#define _H_PUNK_OPENGL_RENDER_TARGET

#include "../../config.h"

namespace OpenGL
{
	enum RenderTargetType { RENDER_TARGET_NONE = 0, RENDER_TARGET_BACK_BUFFER, RENDER_TARGET_TEXTURE_2D };
	enum BufferType {COLOR_BUFFER = 1, DEPTH_BUFFER = 2, STENCIL_BUFFER = 4};

	class PUNK_ENGINE RenderTarget
	{
	protected:
		int m_clear_mask;
		float m_r, m_g, m_b, m_a;

		void ClearTarget();

	public:
		
		struct PUNK_ENGINE Properties
		{
			RenderTargetType m_type;
			int m_clear_mask;
			float m_r, m_g, m_b, m_a;

			Properties();
		};

	public:

		void SetViewport(float x, float y, float width, float height);
		void SetClearMask(int mask);
		void SetClearColor(float r, float g, float b, float a);
		virtual bool Init(Properties* props);
		virtual void Activate();
		virtual void Deactivate();
		virtual ~RenderTarget();
		
	};
}

#endif	//	_H_PUNK_OPENGL_RENDER_TARGET