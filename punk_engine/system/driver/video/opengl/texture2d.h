/*
File: Texture2D.h
Author: Abramau Mikalai
Description: Contains a Texture2D class
*/

#ifndef _H_PUNK_TEXTURE_2D
#define _H_PUNK_TEXTURE_2D

#include "config.h"
#include "../../../../system/resource.h"
#include "../../../../system/buffer.h"
#include "../../../../images/formats.h"

namespace ImageModule
{
	class Image;
}

namespace OpenGL
{
	struct Texture2DImpl;

	class MODULE_OPENGL Texture2D
	{
	protected:
		std::auto_ptr<Texture2DImpl> impl_texture_2d;
	public:
		explicit Texture2D(const ImageModule::Image& image);
		Texture2D(const Texture2D& texture);
		Texture2D& operator = (const Texture2D& texture);
		~Texture2D();
		void Bind() const;
		void Unbind() const;		
	};
}

#endif	// _H_Texture2D
