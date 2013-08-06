#include "exporter.h"
#include "png_exporter.h"
#include "../error/module.h"
#include "../internal_images/image.h"
#include "../../string/string.h"

namespace ImageModule
{
	void Exporter::Export(const System::string& filename, const Image& image)
    {
        if (filename.EndWith(".png"))
		{
			PngExporter importer;
			importer.Export(filename, image);			
		}
		else
			throw ImageException(L"Unsupported file format");
	}
}
