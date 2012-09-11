#ifndef _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE
#define _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE

#include <memory>
#include "render_target.h"

namespace OpenGL
{
	class Texture2D;

	class PUNK_ENGINE RenderTargetTexture : public RenderTarget
	{
	public:

		struct PUNK_ENGINE RenderTargetTextureProperties : public Properties
		{
			int m_texture_width;
			int m_texture_height;
			RenderTargetTextureProperties();
		};

	public:
		RenderTargetTexture();
		void Init(int width, int height);
		virtual bool Init(Properties* props);
		virtual void Activate();
		virtual void Deactivate();
		virtual ~RenderTargetTexture();
		Texture2D* GetColorBuffer();
		Texture2D* GetDepthBuffer();
	private:
		void Clear();
		void Check();
		std::auto_ptr<Texture2D> m_color_texture;
		///	
		std::auto_ptr<Texture2D> m_depth_texture;
		///	multisample resolve target
		unsigned m_resolve_fb;
		///	render frame buffer
		unsigned m_fb;
		///	contains color information
		unsigned m_color_rb;
		///	contains depth information
		unsigned m_depth_rb;
	};
}

#endif