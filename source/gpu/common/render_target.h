#ifndef _H_PUNK_RENDER_TARGET
#define _H_PUNK_RENDER_TARGET

#include "../../config.h"
#include "../../math/rect.h"

namespace GPU
{
	enum RenderTargetType { RENDER_TARGET_NONE = 0, RENDER_TARGET_BACK_BUFFER, RENDER_TARGET_TEXTURE_2D };
	enum BufferType {COLOR_BUFFER = 1, DEPTH_BUFFER = 2, STENCIL_BUFFER = 4};

	class PUNK_ENGINE RenderTarget
	{
	public:

		struct PUNK_ENGINE Properties
		{
			RenderTargetType m_type;
			int m_clear_mask;
			float m_r, m_g, m_b, m_a;
			Properties();
		};

	public:

		void SetClearMask(int mask);
		void SetClearColor(float r, float g, float b, float a);
		
		virtual void SetViewport(const Math::Rect& value) = 0;
		virtual bool Init(Properties* props) = 0;
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
		virtual ~RenderTarget();

	protected:
		int m_clear_mask;
		float m_r, m_g, m_b, m_a;		
	};
}

#endif	//	_H_PUNK_OPENGL_RENDER_TARGET
