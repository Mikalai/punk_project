#include <algorithm>
#include <string>
#include "../../system/environment.h"
#include "../error/module.h"
#include "importer.h"
#include "importer_impl.h"
#include "../internal_images/rgba_image.h"
#include "../internal_images/rgb_image.h"
#include "../internal_images/gray_image.h"
#include "../internal_images/image_impl.h"
#include "../../system/logger.h"
#include "png_importer.h"
#include "jpg_importer.h"

namespace ImageModule
{
	Importer::Importer()
		: Image()
	{}

	Image* Importer::LoadAnyImage(const System::string& filename)
	{
		if (Load(filename))
		{
			Image* image = new Image();
			std::swap(image->impl_image, impl_image);

			return image;
		}
		return nullptr;
	}

	RGBAImage* Importer::LoadRGBA(const System::string& filename)
	{
		Load(filename);
        if (impl_image->m_channels != 4)
            throw ImageException(System::string("{0} is not an RGBA image").arg(filename));
		RGBAImage* rgba_image = new RGBAImage;
		std::swap(rgba_image->impl_image, impl_image);
		return rgba_image;
	}

	RGBImage* Importer::LoadRGB(const System::string& filename)
	{
		Load(filename);
        if (impl_image->m_channels != 3)
            throw ImageException(System::string("{0} is not an RGB image").arg(filename));
		RGBImage* rgb_image = new RGBImage;
		std::swap(rgb_image->impl_image, impl_image);
		return rgb_image;
	}

	GrayImage* Importer::LoadGray(const System::string& filename)
	{
		Load(filename);
        if (impl_image->m_channels != 1)
            throw ImageException(System::string("{0} is not an Alpha image").arg(filename));
		GrayImage* gray_image = new GrayImage;
		std::swap(gray_image->impl_image, impl_image);
		return gray_image;
	}

	bool Importer::Load(const System::string& filename)
	{
        auto file = filename.AsLower();
        if (file.EndWith(".png"))
		{
			PngImporter importer;
			importer.Load(filename);
			std::swap(impl_image, importer.impl_image);
			return true;
		}		
        else if (file.EndWith(".jpeg") || file.EndWith(".jpg"))
		{
			JpgImporter importer;
			importer.Load(filename);
			std::swap(impl_image, importer.impl_image);
			return true;
		}
		else		
            throw ImageException("Unsupported file format");
	}
}
