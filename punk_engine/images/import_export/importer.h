#ifndef _H_PUNK_IMAGE_MODULE_IMPORTER
#define _H_PUNK_IMAGE_MODULE_IMPORTER

#include <memory>
#include "../config.h"

namespace System
{
	class string;
}

namespace ImageModule
{
	class Image;
	class RGBAImage;
	class RGBImage;
	class GrayImage;

	class MODULE_IMAGE Importer
	{
	protected:
		struct ImporterImpl;
		std::auto_ptr<ImporterImpl> impl_importer;
	public:
		Importer();
		RGBAImage LoadRGBA(const System::string& filename);
		RGBImage LoadRGB(const System::string& filename);
		GrayImage LoadGray(const System::string& filename);
	protected:
		virtual void Load(const System::string& filename);
	};
};

#endif