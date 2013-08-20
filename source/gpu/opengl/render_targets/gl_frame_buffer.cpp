#include "../driver/module.h"
#include "../textures/module.h"
#include "../../common/frame_buffer/frame_buffer_config.h"
#include "gl_frame_buffer_convert.h"
#include "gl_frame_buffer.h"

namespace Gpu
{
    static int count = 0;
    namespace OpenGL
    {
        OpenGLFrameBuffer::OpenGLFrameBuffer(VideoDriver *driver)
            : FrameBuffer(driver)
            , m_color_rb(nullptr)
            , m_depth_rb(nullptr)
            , m_resolve_rb(nullptr)
            , m_fb(0)
        {            
            count++;
            GL_CALL(glGenFramebuffers(1, &m_fb));            
        }

        void OpenGLFrameBuffer::Config(FrameBufferConfig* config)
        {
            Gpu::FrameBuffer::Config(config);
            Clear();

            count++;
            GL_CALL(glGenFramebuffers(1, &m_fb));

            m_color_texture = GetVideoDriver()->CreateTexture2D(
                        config->Width(),
                        config->Height(),
                        config->ColorFormat(),
                        ImageModule::IMAGE_FORMAT_RGBA, ImageModule::IMAGE_DATA_TYPE_FLOAT, 0, true);

            if (GetVideoDriver()->GetCaps().IsMultisamplingEnabled)
            {
                m_resolve_rb = new OpenGLFrameBuffer(GetVideoDriver());
                m_resolve_rb->AttachColorTarget(0, m_color_texture);

              //  Bind();
                m_color_rb = new OpenGLColorRenderBuffer(config, GetVideoDriver());
                AttachColorTarget(0, m_color_rb);

             //   Bind();
                m_depth_rb = new OpenGLDepthRenderBuffer(config, GetVideoDriver());
                AttachDepthTarget(m_depth_rb);
            }
            else
            {
                m_depth_texture = GetVideoDriver()->CreateTexture2D(
                            config->Width(),
                            config->Height(),
                            config->DepthFormat(),
                            ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT, ImageModule::IMAGE_DATA_TYPE_FLOAT, 0, false);
                AttachColorTarget(0, m_color_texture);
                AttachDepthTarget(m_depth_texture);           
            }
            Bind();
            Check();
            Unbind();

            CheckConfigCompatibility();
        }

        void OpenGLFrameBuffer::CheckConfigCompatibility()
        {
            //  next code is deprecated in gl 3.3
//            Bind();
//            GLint value;
//            GL_CALL(glGetIntegerv(GL_RED_BITS, &value));
//            if (value != Config()->RedBitsCount())
//                throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");

//            GL_CALL(glGetIntegerv(GL_DEPTH_BITS, &value));
//            if (value != Config()->DepthBitsCount())
//                throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");

//            if (GetVideoDriver()->IsMultisamplingEnabled())
//            {
//                m_resolve_rb->Bind();
//                GL_CALL(glGetIntegerv(GL_RED_BITS, &value));
//                if (value != Config()->RedBitsCount())
//                    throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");
//                m_resolve_rb->Unbind();
//            }
//            Unbind();
        }

        OpenGLFrameBuffer::~OpenGLFrameBuffer()
        {
            Clear();
        }

        void OpenGLFrameBuffer::Clear()
        {
            if (m_color_rb)
            {
                delete m_color_rb;
                m_color_rb = nullptr;
            }
            if (m_depth_rb)
            {
                delete m_depth_rb;
                m_depth_rb = nullptr;
            }
            if (m_resolve_rb)
            {
                delete m_resolve_rb;
                m_resolve_rb = nullptr;
            }
            if (m_fb)
            {                
                GL_CALL(glDeleteFramebuffers(1, &m_fb));
                count--;
                m_fb = 0;
            }
        }

        void OpenGLFrameBuffer::Bind()
        {
            GL_CALL(glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&m_prev_fb));
            if (m_prev_fb != m_fb)
            {
                GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_fb));
            }
        }

        void OpenGLFrameBuffer::Unbind()
        {            
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
            if (m_resolve_rb)
            {
                GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fb));
                GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolve_rb->m_fb));
                GL_CALL(glBlitFramebuffer(0, 0, Config()->Width(), Config()->Height(), 0, 0, Config()->Width(), Config()->Height(), GL_COLOR_BUFFER_BIT, GL_NEAREST));
            }
            if (m_prev_fb != m_fb)
            {
                GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_prev_fb));
            }
        }

        void OpenGLFrameBuffer::AttachColorTarget(size_t index, Texture2D* buffer)
        {
            Texture2DImpl* impl = (Texture2DImpl*)buffer;
            Bind();
            GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, impl->GetIndex(), 0));
            buffer->Bind();
            Check();
            Unbind();
        }

        void OpenGLFrameBuffer::AttachColorTarget(size_t index, ColorRenderBuffer* b)
        {
            OpenGLColorRenderBuffer* buffer = dynamic_cast<OpenGLColorRenderBuffer*>(b);
            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, buffer->Index()));
            Check();
            Unbind();
        }

        void OpenGLFrameBuffer::AttachDepthTarget(Texture2D* buffer)
        {
            Texture2DImpl* impl = (Texture2DImpl*)buffer;
            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, impl->GetIndex(), 0));
            Check();
            Unbind();
        }

        void OpenGLFrameBuffer::AttachDepthTarget(DepthRenderBuffer* b)
        {
            OpenGLDepthRenderBuffer* buffer = dynamic_cast<OpenGLDepthRenderBuffer*>(b);
            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer->Index()));
            Check();
            Unbind();
        }

        void OpenGLFrameBuffer::AttachDepthTarget(Texture2DArray *b, size_t index)
        {
            Texture2DArrayImpl* buffer = dynamic_cast<Texture2DArrayImpl*>(b);
            Bind();
            GL_CALL(glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, buffer->GetId(), 0, index));
            Check();
            Unbind();
        }

        void OpenGLFrameBuffer::SetRenderTarget(FrameBufferTarget value)
        {
            Bind();
            GL_CALL(glDrawBuffer(Convert(value)));
            Unbind();
        }

        void OpenGLFrameBuffer::SetViewport(int x, int y, int width, int height)
        {
            Bind();
            GL_CALL(glViewport(x, y, width, height));
            Unbind();
        }

        void OpenGLFrameBuffer::Clear(bool color, bool depth, bool stencil)
        {
            Bind();
            GLenum flag = 0;
            if (color)
                flag |= GL_COLOR_BUFFER_BIT;
            if (depth)
                flag |= GL_DEPTH_BUFFER_BIT;
            if (stencil)
                flag |= GL_STENCIL_BUFFER_BIT;
            GL_CALL(glClearDepth(1));
            GL_CALL(glClear(flag));            
            Unbind();
        }

        void OpenGLFrameBuffer::Check()
        {
            GL_CALL(GLenum result = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER));
            if (result == GL_FRAMEBUFFER_COMPLETE)
                return;
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

        void OpenGLFrameBuffer::SetPolygonOffset(float a, float b)
        {
            GL_CALL(glPolygonOffset(a, b));
            if (a == 0 && b == 0)
            {
                GL_CALL(glDisable(GL_POLYGON_OFFSET_FILL));
            }
            else
            {
                GL_CALL(glEnable(GL_POLYGON_OFFSET_FILL));
            }
        }
    }
}
