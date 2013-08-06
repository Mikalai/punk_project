#ifndef _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE
#define _H_PUNK_OPENGL_RENDER_TARGET_TEXTURE

#include <memory>
#include "../../../system/smart_pointers/module.h"
#include "../../common/render_target.h"

namespace Gpu
{
	class Texture2D;

	namespace OpenGL
	{
        class PUNK_ENGINE_API RenderTargetTextureColorDepth : public RenderTarget
		{			
		public:
            RenderTargetTextureColorDepth(Texture2D* color_buffer, Texture2D* depth_buffer, VideoDriver* driver);
            virtual ~RenderTargetTextureColorDepth();
		//	void Init(int width, int height);
			            
            virtual void SetViewport(const Math::Rect& v) override;
            virtual void Activate() override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual void Deactivate() override;            

			Texture2D* GetColorBuffer();
			Texture2D* GetDepthBuffer();

		private:
            void Destroy();
			void Check();

            ///	render frame buffer
            unsigned m_fb;
            ///	multisample resolve target
			unsigned m_resolve_fb;			
			///	contains color information
			unsigned m_color_rb;
			///	contains depth information
			unsigned m_depth_rb;

            ///	Should not be destroyed in destructor
			Texture2D* m_color_texture;
            ///	Should not be destroyed in destructor
			Texture2D* m_depth_texture;
		};
	}
}

#endif
