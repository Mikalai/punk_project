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
		: impl_importer(new ImporterImpl())
	{}

	RGBAImage Importer::LoadRGBA(const System::string& filename)
	{
		Load(filename);
		if (impl_importer->GetComponentsCount() != 4)
			throw ImageError((filename + L" is not an RGBA image").Data());
		RGBAImage rgba_image;
		Image& image = rgba_image;
		image = *impl_importer;
		return rgba_image;
	}

	RGBImage Importer::LoadRGB(const System::string& filename)
	{
		Load(filename);
		if (impl_importer->GetComponentsCount() != 3)
			throw ImageError((filename + L" is not an RGB image").Data());
		RGBImage rgb_image;
		Image& image = rgb_image;
		image = *impl_importer;
		return rgb_image;
	}

	GrayImage Importer::LoadGray(const System::string& filename)
	{
		Load(filename);
		if (impl_importer->GetComponentsCount() != 1)
			throw ImageError((filename + L" is not an RGB image").Data());
		GrayImage gray_image;
		Image& image = gray_image;
		image = *impl_importer;
		return gray_image;
	}

	void Importer::Load(const System::string& filename)
	{
		std::wstring file(filename.Data());
		if (file.rfind(L".png") != std::wstring::npos)
		{
			PngImporter importer;
			importer.Load(filename);
			std::swap(impl_importer, importer.impl_importer);
		}
		else
			throw ImageError(L"Unsupported file format");
	}
}