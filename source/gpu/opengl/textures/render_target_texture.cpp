#include "render_target_texture.h"
#include "../textures/texture2d.h"
#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderTargetTexture::RenderTargetTextureProperties::RenderTargetTextureProperties()
			: Properties()
			, m_texture_width(512)
			, m_texture_height(512)
		{
			m_type = RENDER_TARGET_TEXTURE_2D;
		}

		RenderTargetTexture::RenderTargetTexture()
			: m_fb(0)
			, m_resolve_fb(0)
			, m_color_rb(0)
			, m_depth_rb(0)
		{}


		bool RenderTargetTexture::Init(RenderTarget::Properties* props)
		{
			RenderTargetTextureProperties* p = static_cast<RenderTargetTextureProperties*>(props);
			Clear();

			//	generate frame buffer
			glGenFramebuffers(1, &m_fb);
			//	create color texture
			m_color_texture.reset(new Texture2D);
			m_color_texture->Create(p->m_texture_width, p->m_texture_height, ImageModule::IMAGE_FORMAT_RGBA8, 0);

			//	if multisample
			//	generate render buffers
			glGenRenderbuffers(1, &m_depth_rb);
			glGenRenderbuffers(1, &m_color_rb);
			//	generate resolve frame buffer
			glGenFramebuffers(1, &m_resolve_fb);

			//	tune resolve frame buffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_resolve_fb);
			//	bind color texture
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->GetCode(), 0);

			Check();

			//	tune render frame buffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_fb);

			//	tune color render buffer
			glBindRenderbuffer(GL_RENDERBUFFER, m_color_rb);

			int max_samples;
			glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
			//	for csaa some extra staff needed
			// create a regular MSAA color buffer
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, max_samples, GL_RGBA8, m_color_texture->GetWidth(), m_color_texture->GetHeight());
			// check the number of samples
			glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &max_samples);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_rb);

			Check();

			//	tune depth render buffer
			glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rb);

			//	for csaa another method should be used
			//	create a regular MSAA depth buffer
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, max_samples, GL_DEPTH_COMPONENT24, m_color_texture->GetWidth(), m_color_texture->GetHeight());

			//	attach depth buffer to frame buffer
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rb);

			Check();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			return true;
		}

		void RenderTargetTexture::Clear()
		{
			glDeleteFramebuffers(1, &m_fb);
			CHECK_GL_ERROR(L"Can't delete frame buffer object");
			glDeleteFramebuffers(1, &m_resolve_fb);
			CHECK_GL_ERROR(L"Can't delete resolve frame buffer object");
			glDeleteRenderbuffers(1, &m_color_rb);
			CHECK_GL_ERROR(L"Can't delete color render buffer object");
			glDeleteRenderbuffers(1, &m_depth_rb);
			CHECK_GL_ERROR(L"Can't delete depth render buffer object");
			m_color_texture.reset(0);
			m_depth_texture.reset(0);
		}

		RenderTargetTexture::~RenderTargetTexture()
		{
			Clear();
		}

		void RenderTargetTexture::Activate()
		{
			glDepthFunc(GL_LEQUAL);
			CHECK_GL_ERROR(L"Can't set depth func to GL_EQUAL");
			glBindFramebuffer(GL_FRAMEBUFFER, m_fb);
			CHECK_GL_ERROR(L"Can't bind frame buffer");
			ClearTarget();
		}

		void RenderTargetTexture::Deactivate()
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fb);
			CHECK_GL_ERROR(L"Can't bind read frame buffer");
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolve_fb);
			CHECK_GL_ERROR(L"Can't bind draw frame buffer");
			glBlitFramebuffer(0, 0, m_color_texture->GetWidth(), m_color_texture->GetHeight(), 0, 0, m_color_texture->GetWidth(), m_color_texture->GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
			CHECK_GL_ERROR(L"Can't blit frame buffer");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			CHECK_GL_ERROR(L"Can't unbind frame buffer");

			glBindTexture(GL_TEXTURE_2D, m_color_texture->GetCode());
			CHECK_GL_ERROR(L"Can't bind texture");
			glGenerateMipmap(GL_TEXTURE_2D);
			CHECK_GL_ERROR(L"Can't generate mipmaps");
			glBindTexture(GL_TEXTURE_2D, 0);
			CHECK_GL_ERROR(L"Can't unbind texture");
			glDepthFunc(GL_LESS);
			CHECK_GL_ERROR(L"Can't set depth func to GL_LESS");
		}

		Texture2D* RenderTargetTexture::GetColorBuffer()
		{
			return m_color_texture.get();
		}

		Texture2D* RenderTargetTexture::GetDepthBuffer()
		{
			return m_depth_texture.get();
		}

		void RenderTargetTexture::Check()
		{
			GLenum result = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER);
			if (result == GL_FRAMEBUFFER_COMPLETE)
				out_message() << L"Frame buffer complete" << std::endl;
			else if (result == GL_FRAMEBUFFER_UNDEFINED)
				out_error() << L"GL_FRAMEBUFFER_UNDEFINED is returned if target is the default framebuffer, but the default framebuffer does not exist" << std::endl;
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT is returned if any of the framebuffer attachment points are framebuffer incomplete" << std::endl;
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT is returned if the framebuffer does not have at least one image attached to it" << std::endl;
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi" << std::endl;		
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER." << std::endl;		
			else if (result == GL_FRAMEBUFFER_UNSUPPORTED)
				out_error() << L"GL_FRAMEBUFFER_UNSUPPORTED is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions." << std::endl;		
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES." << std::endl;		
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures." << std::endl;		
			else if (result == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
				out_error() << L"GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target." << std::endl;		
			else 
				out_error() << L"Fuck" << std::endl;
		}
	}
}