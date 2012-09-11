#ifndef _H_PUNK_IMAGE_MODULE_PNG_IMPORTER
#define _H_PUNK_IMAGE_MODULE_PNG_IMPORTER

#include "importer.h"

namespace ImageModule
{
	class Image;

	class PngImporter : public Importer
	{
	public:
		PngImporter();

		virtual void Load(const System::string& filename);
		virtual void Load(std::istream& stream, Image* image);

		friend class Importer;
	};
}

#endif