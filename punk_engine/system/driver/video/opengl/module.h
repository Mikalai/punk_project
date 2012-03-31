#ifndef _H_PUNK_OPENGL_DRIVER_MODULE
#define _H_PUNK_OPENGL_DRIVER_MODULE

#include "config.h"
#include "../../../module.h"

namespace OpenGL
{
	class MODULE_OPENGL Module : public System::Module
	{
	public:
		virtual void Init();
		virtual void Destroy();
		virtual ~Module();

		static const wchar_t* NAME();
		static unsigned short TEXTURE_2D_RESOURCE_TYPE();
		static unsigned short VAO_RESOURCE_TYPE();
	};
}

#endif