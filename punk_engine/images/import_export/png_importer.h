#ifndef _H_PUNK_IMAGE_MODULE_PNG_IMPORTER
#define _H_PUNK_IMAGE_MODULE_PNG_IMPORTER

#include "importer.h"

namespace ImageModule
{
	class PngImporter : public Importer
	{
	protected:
		PngImporter();

		virtual void Load(const System::string& filename);

		friend class Importer;
	};
}

#endif