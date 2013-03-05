#ifndef _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE
#define _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE

#include <memory>
#include "../../../system/smart_pointers/module.h"
#include "gl_render_target.h"

namespace GPU
{
	class Texture2D;

	namespace OpenGL
	{
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
			
			void SetViewport(float x, float y, float width, float height) override;
			bool Init(Properties* props) override;
			void Activate() override;
			void Deactivate() override;

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
			///	Contains information about internal texture size
			RenderTargetTextureProperties m_properties;
		};
	}
}

#endif