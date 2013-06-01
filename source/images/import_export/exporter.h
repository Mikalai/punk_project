#ifndef _H_PUNK_IMAGE_EXPORTER
#define _H_PUNK_IMAGE_EXPORTER

#include "../../config.h"

namespace System
{
	class string;
}

namespace ImageModule
{
	class Image;

	class PUNK_ENGINE_PUBLIC Exporter
	{
	public:
		virtual void Export(const System::string& filename, const Image& image);
	};
}

#endif