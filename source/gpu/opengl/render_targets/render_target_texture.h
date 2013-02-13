#ifndef _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE
#define _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE

#include <memory>
#include "../../../system/smart_pointers/module.h"
#include "gl_render_target.h"

namespace GPU
{
	namespace OpenGL
	{
		class Texture2D;

		class PUNK_ENGINE RenderTargetTexture : public OpenGLRenderTarget
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
			virtual ~RenderTargetTexture();
		//	void Init(int width, int height);
			virtual bool Init(Properties* props);
			virtual void Activate();
			virtual void Deactivate();
			Texture2D* GetColorBuffer();
			Texture2D* GetDepthBuffer();

		private:
			void Clear();
			void Check();
			///	multisample resolve target
			unsigned m_resolve_fb;
			///	render frame buffer
			unsigned m_fb;
			///	contains color information
			unsigned m_color_rb;
			///	contains depth information
			unsigned m_depth_rb;

			///	Should be destroyed in destructor
			Texture2D* m_color_texture;
			///	Should be destroyed in destructor
			Texture2D* m_depth_texture;

		};
	}
}

#endif