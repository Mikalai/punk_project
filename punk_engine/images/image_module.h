#ifndef _H_PUNK_IMAGE_IMAGE_MODULE
#define _H_PUNK_IMAGE_IMAGE_MODULE

#include "config.h"
#include "../system/module.h"

namespace ImageModule
{
	class Module : public System::Module
	{
	public:
		virtual void Init();
		virtual void Destroy();
		virtual ~Module();

		static const wchar_t* NAME();
		static unsigned short RGBA_IMAGE_RESOURCE_TYPE_CODE();
		static unsigned short RGB_IMAGE_RESOURCE_TYPE_CODE();
		static unsigned short GRAY_IMAGE_RESOURCE_TYPE_CODE();
	};
};

#endif