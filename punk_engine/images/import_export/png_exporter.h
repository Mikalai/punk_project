#ifndef _H_PUNK_IMAGE_PNG_EXPORTER
#define _H_PUNK_IMAGE_PNG_EXPORTER

#include "exporter.h"

namespace ImageModule
{
	class PngExporter : public Exporter
	{
	public:
		virtual void Export(const System::string& filename, const Image& image);
	};
}

#endif