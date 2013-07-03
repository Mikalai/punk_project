#ifdef USE_LIB_TIFF
#ifndef _H_PUNK_IMAGE_MODULE_TIFF_IMPORTER
#define _H_PUNK_IMAGE_MODULE_TIFF_IMPORTER

#include "importer.h"

namespace ImageModule
{
    class Image;

    class TiffImporter : public Importer
    {
    public:
        TiffImporter();

        virtual bool Load(const System::string& filename);
        virtual bool Load(std::istream& stream, Image* image);

        friend class Importer;
    };
}

#endif  //  _H_PUNK_IMAGE_MODULE_TIFF_IMPORTER
#endif  //  USE_LIB_TIFF
