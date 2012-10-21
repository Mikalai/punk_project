#include "importer.h"
#include "importer_impl.h"
#include "../error.h"
#include "../internal_images/rgba_image.h"
#include "../internal_images/rgb_image.h"
#include "../internal_images/gray_image.h"
#include "../internal_images/image_impl.h"
#include "png_importer.h"
#include "../../system/logger.h"
#include <string>

namespace ImageModule
{
	Importer::Importer()
		: Image()
	{}

	Image* Importer::LoadAnyImage(const System::string& filename)
	{
		Load(filename);

		Image* image = new Image();
		std::swap(image->impl_image, impl_image);

		return image;
	}

	RGBAImage* Importer::LoadRGBA(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 4)
			throw ImageError((filename + L" is not an RGBA image").Data());
		RGBAImage* rgba_image = new RGBAImage;
		std::swap(rgba_image->impl_image, impl_image);
		return rgba_image;
	}

	RGBImage* Importer::LoadRGB(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 3)
			throw ImageError((filename + L" is not an RGB image").Data());
		RGBImage* rgb_image = new RGBImage;
		std::swap(rgb_image->impl_image, impl_image);
		return rgb_image;
	}

	GrayImage* Importer::LoadGray(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 1)
			throw ImageError((filename + L" is not an RGB image").Data());
		GrayImage* gray_image = new GrayImage;
		std::swap(gray_image->impl_image, impl_image);
		return gray_image;
	}

	bool Importer::Load(const System::string& filename)
	{
		std::wstring file(filename.Data());
		if (file.rfind(L".png") != std::wstring::npos)
		{
			PngImporter importer;
			importer.Load(filename);
			std::swap(impl_image, importer.impl_image);
			return true;
		}
		else
		{
			out_error() << L"Unsupported file format" << std::endl;
			return false;
		}		
	}
}