#include "exporter.h"
#include "png_exporter.h"
#include "../internal_images/image.h"
#include "../../system/string.h"
#include "../../system/error.h"

namespace ImageModule
{
	void Exporter::Export(const System::string& filename, const Image& image)
	{
		std::wstring file(filename.Data());
		if (file.rfind(L".png") != std::wstring::npos)
		{
			PngExporter importer;
			importer.Export(filename, image);			
		}
		else
			throw System::SystemError(L"Unsupported file format");
	}
}