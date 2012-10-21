#ifndef _H_PUNK_IMAGE_MODULE_IMPORTER
#define _H_PUNK_IMAGE_MODULE_IMPORTER

#include <memory>
#include "../../config.h"
#include "../internal_images/image.h"
namespace System
{
	class string;
}

namespace ImageModule
{
	class RGBAImage;
	class RGBImage;
	class GrayImage;

	class PUNK_ENGINE Importer : public Image
	{
	//protected:
		//struct ImporterImpl;
		//std::auto_ptr<ImporterImpl> impl_importer;
	public:
		Importer();
		RGBAImage* LoadRGBA(const System::string& filename);
		RGBImage* LoadRGB(const System::string& filename);
		GrayImage* LoadGray(const System::string& filename);

		Image* LoadAnyImage(const System::string& filename);

	protected:
		virtual bool Load(const System::string& filename);
	};
};

#endif