/*
File: FrameBuffer.h
Author: Abramau Mikalai
Description: Calss for rendering to texture.
Simply now i don't know what for
frame buffer object can be used else
*/

#ifndef _H_PUNK_FRAME_BUFFER_OBJECT
#define _H_PUNK_FRAME_BUFFER_OBJECT

#include "gl/gl3.h"
#include "texture2d.h"
#include "config.h"

namespace OpenGL
{
	class MODULE_OPENGL FrameBuffer
	{
		FrameBuffer(const FrameBuffer&);
		FrameBuffer& operator = (const FrameBuffer&);
	protected:
		//	color texture
		std::auto_ptr<Texture2D> m_color_texture;
		//	depth texture
		std::auto_ptr<Texture2D> m_depth_texture;
		//	multisample resolve target
		GLuint m_resolve_fb;
		//	render frame buffer
		GLuint m_fb;
		//	contains color information
		GLuint m_color_rb;
		//	contains depth information
		GLuint m_depth_rb;

		void Check();
		virtual void Clear();
	public:
		FrameBuffer();
		virtual ~FrameBuffer();
		virtual void Init(GLint width, GLint height);
		void Activate();
		void Deactivate();
		Texture2D* GetColorTexture();
		Texture2D* GetDepthTexture();
	};
}
#endif	//_H_FRAME_BUFFER_OBJECT
