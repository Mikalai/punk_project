#include "frame_buffer_with_depth.h"
#include "extensions.h"
#include "driver.h"

namespace OpenGL
{

	FrameBufferWithDepth::FrameBufferWithDepth()
		: FrameBuffer()
	{}

	void FrameBufferWithDepth::Init(GLint width, GLint height)
	{
		//m_texture_2d.reset(new Texture2D);
		//m_texture_2d->Create(width, height, GL_DEPTH_COMPONENT24, 0);
		//////
		//////	Create texture
		//////
		////glGenTextures(1, &m_texture);
		////glBindTexture(GL_TEXTURE_2D, m_texture);
		////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		////glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH, GL_UNSIGNED_BYTE, 0);

		//CHECK_GL_ERROR(L"Can't create texture for frame buffer with depth");
		//
		////
		////	create frame buffer
		////
		//if (!m_fbo)
		//{
		//	glDeleteFramebuffers(1, &m_fbo);
		//	CHECK_GL_ERROR(L"Can't delete frame buffer");
		//}
		//glGenFramebuffers(1, &m_fbo);
		//CHECK_GL_ERROR(L"Can't generate frame buffer");
		//glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		//CHECK_GL_ERROR(L"Can't bind frame buffer");
		//glDrawBuffer(GL_NONE);
		//CHECK_GL_ERROR(L"Can't set glDrawBuffer");
		//glReadBuffer(GL_NONE);
		//CHECK_GL_ERROR(L"Can't set glReadBuffer");

		////
		////	attach created texture
		////
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture_2d->GetCode(), 0);
		//CHECK_GL_ERROR(L"Can't bind texture to frame buffer");

		////SMART_LOG(CheckError("Can't create frame buffer object"), LOG_LOCATION, true)

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//CHECK_GL_ERROR(L"Can't unbind frame buffer");

		//Check();
	}

	FrameBufferWithDepth::~FrameBufferWithDepth()
	{
		//glDeleteFramebuffers(1, &m_fbo);	
		//CHECK_GL_ERROR(L"Can't delete frame buffer");
	}
}