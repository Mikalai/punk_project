#include "render_target_texture_color.h"
#include "../textures/module.h"
#include "../gl/module.h"
#include "../textures/texture2d_pbo_impl.h"

namespace Gpu
{
    namespace OpenGL
    {
        RenderTargetTextureColor::RenderTargetTextureColor(Texture2D *color_buffer, VideoDriver* driver)
            : RenderTarget(driver)
            , m_color_buffer{color_buffer}
            , m_fb{0}
            , m_depth_rb{0}
        {
            GL_CALL(glGenFramebuffers(1, &m_fb));
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_fb));

            GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_buffer->impl->m_texture_id, 0));

            GL_CALL(glGenRenderbuffers(1, &m_depth_rb));
            GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rb));
            GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_color_buffer->GetWidth(), m_color_buffer->GetHeight()));

            GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rb));

            Check();

            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }

        RenderTargetTextureColor::~RenderTargetTextureColor()
        {
            GL_CALL(glDeleteRenderbuffers(1, &m_depth_rb));
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
            GL_CALL(glDeleteFramebuffers(1, &m_fb));
        }

        void RenderTargetTextureColor::SetViewport(const Math::Rect& value)
        {
            RenderTarget::SetViewport(value);
        }

        void RenderTargetTextureColor::Activate()
        {
            GL_CALL(glDepthFunc(GL_LEQUAL));
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_fb));
            GL_CALL(glViewport(0, 0, m_color_buffer->GetWidth(), m_color_buffer->GetHeight()));
            Clear(true, true, false);
        }

        void RenderTargetTextureColor::Deactivate()
        {
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }

        void RenderTargetTextureColor::Clear(bool color, bool depth, bool stencil)
        {
            auto c = GetClearColor();
            GL_CALL(glClearColor(c.X(), c.Y(), c.Z(), c.W()));
            GL_CALL(glClearDepth(GetClearDepth()));

            GLbitfield b = 0;

            if (color)
                b |= GL_COLOR_BUFFER_BIT;
            if (depth)
                b |= GL_DEPTH_BUFFER_BIT;
            if (stencil)
                b |= GL_STENCIL_BUFFER_BIT;

            GL_CALL(glClear(b));
        }

        void RenderTargetTextureColor::Check()
        {
            GL_CALL(GLenum result = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER));
            if (result == GL_FRAMEBUFFER_COMPLETE)
                ;/*out_message() << L"Frame buffer complete" << std::endl;*/
            else if (result == GL_FRAMEBUFFER_UNDEFINED)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_UNDEFINED is returned if target is the default framebuffer, but the default framebuffer does not exist");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT is returned if any of the framebuffer attachment points are framebuffer incomplete");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT is returned if the framebuffer does not have at least one image attached to it");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.");
            else if (result == GL_FRAMEBUFFER_UNSUPPORTED)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_UNSUPPORTED is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
                throw System::PunkInvalidArgumentException(L"GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.");
            else
                throw System::PunkInvalidArgumentException(L"Fuck");
        }
    }
}
