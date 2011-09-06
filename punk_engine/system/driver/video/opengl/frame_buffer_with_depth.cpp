#include "frame_buffer_with_depth.h"
#include "driver.h"

namespace OpenGL
{
	void FrameBufferWithDepth::Init(GLint width, GLint height)
	{
		//
		//	Create texture
		//
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH, GL_UNSIGNED_BYTE, 0);

		if (glGetError() != GL_NO_ERROR)
			throw System::SystemError(L"Can't create texture for frame buffer" + LOG_LOCATION_STRING);
		glBindTexture(GL_TEXTURE_2D, 0);

		//
		//	create frame buffer
		//
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		//
		//	attach created texture
		//
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture, 0);

		//SMART_LOG(CheckError("Can't create frame buffer object"), LOG_LOCATION, true)

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBufferWithDepth::~FrameBufferWithDepth()
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteTextures(1, &m_texture);
	}

	void FrameBufferWithDepth::Activate()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void FrameBufferWithDepth::Deactivate()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint FrameBufferWithDepth::GetTexture()
	{
		return m_texture;
	}
}