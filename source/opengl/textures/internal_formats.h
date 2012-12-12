#ifndef _H_PUNK_OPENGL_INTERNAL_TEXTURE_FORMATS
#define _H_PUNK_OPENGL_INTERNAL_TEXTURE_FORMATS

#include "../../config.h"
#include "../../images/formats.h"

namespace OpenGL
{
	int PUNK_ENGINE ImageFormatToOpenGL(ImageModule::ImageFormat format);
}

#endif	//	_H_PUNK_OPENGL_INTERNAL_TEXTURE_FORMATS