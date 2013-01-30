#include <memory>
#include "frame_buffer.h"
#include "driver.h"
#include "static_object.h"
#include "render_context\rc_bump_mapping.h"
#include "texture_context.h"

namespace OpenGL
{
	FrameBuffer::FrameBuffer() 
		: m_fb(0)
		, m_resolve_fb(0)
	{}


	void FrameBuffer::Init(GLint width, GLint height)
	{
		Clear();

		//	generate frame buffer
		glGenFramebuffers(1, &m_fb);
		//	create color texture
		m_color_texture.reset(new Texture2D);
		m_color_texture->Create(width, height, GL_RGBA8, 0);

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
		glGetIntegerv(GL_MAX_SAMPLES_EXT, &max_samples);
		//	for csaa some extra staff needed
		// create a regular MSAA color buffer
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, max_samples, GL_RGBA8, m_color_texture->GetWidth(), m_color_texture->GetHeight());
		// check the number of samples
		glGetRenderbufferParameteriv(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_SAMPLES_EXT, &max_samples);

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
//
//		//glGenTextures(1, &m_texture);
//		//glBindTexture(GL_TEXTURE_2D, m_texture);
//		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//
//		//glBindTexture(GL_TEXTURE_2D, 0);
//
//		//
//		//	create frame buffer
//		//
//		glGenFramebuffers(1, &m_fbo);
//		CHECK_GL_ERROR(L"Can't generate frame buffer");
//		//
//		//	Create render buffer object
//		//
//		glGenRenderbuffers(1, &m_rbo);
//		CHECK_GL_ERROR(L"Can't generate render buffer");
//		//
//		//	Bind created frame buffer
//		//
//		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
//		CHECK_GL_ERROR(L"Can't bind frame buffer");
//		//
//		//	Bind texture
//		//
////		m_texture_2d->Bind();
//		//
//		//	attach created texture
//		//
//		int code = m_texture_2d->GetCode();
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, code, 0);
//		CHECK_GL_ERROR(L"Can't attach texture to the frame buffer");
//		//
//		//	bind created render buffer
//		//
//		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
//		CHECK_GL_ERROR(L"Can't bind render buffer");
//		//
//		//	init storage parameters
//		//
//		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
//		CHECK_GL_ERROR(L"Can't glRenderBufferstorage");
//		//
//		//	attach depth buffer
//		//
//		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
//		CHECK_GL_ERROR(L"Can't attach depth buffer fo frame buffer");
//		Check();
//
//		//glBindRenderbuffer(GL_RENDERBUFFER, 0);
//		//CHECK_GL_ERROR(L"Can't unibnd render target buffer");
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		CHECK_GL_ERROR(L"Can't unbind frame buffer object");
	}

	void FrameBuffer::Clear()
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

	FrameBuffer::~FrameBuffer()
	{
		Clear();
	}

	void FrameBuffer::Activate()
	{
		glDepthFunc(GL_LEQUAL);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fb);
		//static bool init = false;
		//static std::auto_ptr<OpenGL::StaticMesh> m_vao;
		//static std::auto_ptr<OpenGL::RenderContextBumpMapping> m_rc;
		//static std::auto_ptr<OpenGL::TextureContext> m_tc;

		//if (!init)
		//{
		//	m_rc.reset(new OpenGL::RenderContextBumpMapping());
		//	m_tc.reset(new OpenGL::TextureContext());

		//	System::Folder fld;
		//	fld.Open(System::Environment::Instance()->GetModelFolder());
		//	m_vao.reset(new OpenGL::StaticMesh());
		//	m_vao->FromFileVAO(L"m16a2_rifle.vao");
		//	fld.Close();
		//	init = true;
		//}

		//glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		//CHECK_GL_ERROR(L"Can't activate frame buffer");
		//{
		//	GLsync s = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		//	CHECK_GL_ERROR(L"Can't glFenceSync");			
		//	glActiveTexture(GL_TEXTURE0);
		//	CHECK_GL_ERROR(L"Can't glActiveTexture");
		//	{
		//		GLenum bufs[] = {GL_COLOR_ATTACHMENT0};
		//		//glDrawBuffers(1, bufs);
		//		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		//	}
		//	CHECK_GL_ERROR(L"Can't glDrawBuffer");
		//	glClearColor(1, 0, 0, 1);
		//	CHECK_GL_ERROR(L"Can't glClearColor");
		//	//glDisable(GL_BLEND);
		//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//	CHECK_GL_ERROR(L"Can't glClear");

		//	glWaitSync(s, 0, GL_TIMEOUT_IGNORED); 
		//	CHECK_GL_ERROR(L"Can't glWaitSync");
		//	glDeleteSync(s);
		//	CHECK_GL_ERROR(L"Can't glDeleteSync");

		//	unsigned char buf[] = {127,17,17,17};
		//	glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buf);
		//	CHECK_GL_ERROR(L"Can't glReadPixels");
		//}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//CHECK_GL_ERROR(L"Can't glBindFramebuffer");

		//// render to back buffer
		//glClearColor(0, 1, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//m_rc->SetAmbientColor(Math::vec4(1,1,1,1));
		//m_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
		//m_rc->SetLightPosition(Math::vec3(5, 5, 0));
		//m_rc->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0, GetTexture()->GetWidth() / (double)GetTexture()->GetHeight(), 0.1, 100.0));
		//m_rc->SetViewMatrix(Math::mat4::CreateIdentity());
		//m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, -3));
		//m_rc->Begin();

		//GLuint diffuse = GetTexture()->GetCode();
		//GLuint normal = GetTexture()->GetCode();

		//m_tc->Unbind();
		//glActiveTexture(GL_TEXTURE0);
		//CHECK_GL_ERROR(L"Can't glActiveTexture");
		//glBindTexture(GL_TEXTURE_2D, diffuse);
		//CHECK_GL_ERROR(L"Can't glBindTexture");

		////m_tc->SetTexture0(GetTexture());
		////m_tc->SetTexture1(GetTexture());
		////m_tc->Bind();

		//m_vao->Bind(m_rc->GetSupportedVertexAttributes());
		////m_frame_buffer->Activate();
		//m_vao->Render();
		////m_frame_buffer->Deactivate();
		//m_vao->Unbind();
		//m_tc->Unbind();
		//m_rc->End();

	}

	void FrameBuffer::Deactivate()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fb);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolve_fb);
		glBlitFramebuffer(0, 0, m_color_texture->GetWidth(), m_color_texture->GetHeight(), 0, 0, m_color_texture->GetWidth(), m_color_texture->GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glBindTexture(GL_TEXTURE_2D, m_color_texture->GetCode());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDepthFunc(GL_LESS);
		//m_texture_2d->Unbind();
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//CHECK_GL_ERROR(L"Can't deactivate frame buffer");
		

  //      
	}

	Texture2D* FrameBuffer::GetColorTexture()
	{
		return m_color_texture.get();
	}

	Texture2D* FrameBuffer::GetDepthTexture()
	{
		return m_depth_texture.get();
	}

	void FrameBuffer::Check()
	{
//		Activate();
		//CHECK_GL_ERROR(L"Can't activate frame buffer");
		GLenum result = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER);
		if (result == GL_FRAMEBUFFER_COMPLETE)
			System::Logger::Instance()->WriteMessage(L"Frame buffer complete");
		else if (result == GL_FRAMEBUFFER_UNDEFINED)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_UNDEFINED is returned if target is the default framebuffer, but the default framebuffer does not exist");
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT is returned if any of the framebuffer attachment points are framebuffer incomplete");
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT is returned if the framebuffer does not have at least one image attached to it");
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi");		
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.");		else if (result == GL_FRAMEBUFFER_UNSUPPORTED)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_UNSUPPORTED is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");		
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES.");		
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.");		
		else if (result == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
			System::Logger::Instance()->WriteError(L"GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.");		
		else 
			System::Logger::Instance()->WriteError(L"Fuck");

	//	Deactivate();
	}

}
