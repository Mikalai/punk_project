#ifndef _H_PUNK_IMAGE_MODULE_JPG_IMPORTER
#define _H_PUNK_IMAGE_MODULE_JPG_IMPORTER

#include "importer.h"

namespace ImageModule
{
	class Image;

	class JpgImporter : public Importer
	{
	public:
		JpgImporter();

		virtual bool Load(const System::string& filename);
		virtual bool Load(std::istream& stream, Image* image);

		friend class Importer;
	};
}

#endif	//	_H_PUNK_IMAGE_MODULE_JPG_IMPORTER
