/*
File: FrameBufferWithDepth.h
Author: Abramov Nickolai
Description: Calss for rendering to texture.
Simply now i don't know what for
frame buffer object can be used else
*/

#ifndef _H_PUNK_FRAME_BUFFER_OBJECT_WITH_DEPTH
#define _H_PUNK_FRAME_BUFFER_OBJECT_WITH_DEPTH

#include "gl/gl3.h"

namespace OpenGL
{
	class FrameBufferWithDepth
	{
		GLint m_width;
		GLint m_height;
		GLuint m_texture;
		GLuint m_fbo;
		GLint m_oldx;
		GLint m_oldy;
		GLint m_oldWidth;
		GLint m_oldHeight;
	public:
		~FrameBufferWithDepth();
		void Init(GLint width, GLint height);
		void Activate();
		void Deactivate();
		GLuint GetTexture();
	};
}

#endif	//_H_FRAME_BUFFER_OBJECT_WITH_DEPTH
