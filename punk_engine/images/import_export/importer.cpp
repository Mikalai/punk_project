#include "importer.h"
#include "importer_impl.h"
#include "../error.h"
#include "../internal_images/rgba_image.h"
#include "../internal_images/rgb_image.h"
#include "../internal_images/gray_image.h"
#include "../internal_images/image_impl.h"
#include "png_importer.h"
#include <string>

namespace ImageModule
{
	Importer::Importer()
		: Image()
	{}

	RGBAImage Importer::LoadRGBA(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 4)
			throw ImageError((filename + L" is not an RGBA image").Data());
		RGBAImage rgba_image;
		std::swap(rgba_image.impl_image, impl_image);
		return rgba_image;
	}

	RGBImage Importer::LoadRGB(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 3)
			throw ImageError((filename + L" is not an RGB image").Data());
		RGBImage rgb_image;
		std::swap(rgb_image.impl_image, impl_image);
		return rgb_image;
	}

	GrayImage Importer::LoadGray(const System::string& filename)
	{
		Load(filename);
		if (impl_image->m_components != 1)
			throw ImageError((filename + L" is not an RGB image").Data());
		GrayImage gray_image;
		std::swap(gray_image.impl_image, impl_image);
		return gray_image;
	}

	void Importer::Load(const System::string& filename)
	{
		std::wstring file(filename.Data());
		if (file.rfind(L".png") != std::wstring::npos)
		{
			PngImporter importer;
			importer.Load(filename);
			std::swap(impl_image, importer.impl_image);
		}
		else
			throw ImageError(L"Unsupported file format");
	}
}