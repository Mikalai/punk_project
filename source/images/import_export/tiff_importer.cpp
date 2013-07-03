#ifdef USE_LIB_TIFF
#include <tiffio.h>
#include <fstream>
#include "../../string/string.h"
#include "../../system/module.h"

#include "tiff_importer.h"

namespace ImageModule
{
    struct PunkTiffHandle
    {
        std::istream* stream;
        System::string filename;
    };

    TiffImporter::TiffImporter()
    {
    }

    tmsize_t PunkTIFFReadProc(thandle_t h, void* buffer, tmsize_t size)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        handle->stream->read((char*)buffer, size);
        return size;
    }

    tmsize_t PunkTIFFWriteProc(thandle_t, void*, tmsize_t)
    {
        return 0;
    }

    toff_t PunkTIFFSeekProc(thandle_t h, toff_t offset, int pos)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        handle->stream->seekg(offset, (std::ios_base::seekdir)pos);
        return offset;
    }

    int PunkTIFFCloseProc(thandle_t h)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        std::ifstream* s = dynamic_cast<std::ifstream*>(handle->stream);
        if (s)
            s->close();
        return 1;
    }

    toff_t PunkTIFFSizeProc(thandle_t h)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        auto pos = handle->stream->tellg();
        auto res = handle->stream->seekg(0, std::ios_base::end).tellg();
        handle->stream->seekg(pos, std::ios_base::beg);
        return res;
    }

    int PunkTIFFMapFileProc(thandle_t, void** base, toff_t* size)
    {
        return 0;
    }

    void PunkTIFFUnmapFileProc(thandle_t, void* base, toff_t size)
    {

    }

    bool TiffImporter::Load(const System::string &filename)
    {
        std::ifstream stream(filename.ToStdString().c_str());
        if (!stream.is_open())
            throw System::PunkException(L"File not found: " + filename);

        return Load(stream, this);
    }

    bool TiffImporter::Load(std::istream &stream, Image *image)
    {
        PunkTiffHandle h;
        h.stream = &stream;
        TIFF* tif;
        if (!(tif = TIFFClientOpen("", "r", &h, PunkTIFFReadProc,
                       PunkTIFFWriteProc, PunkTIFFSeekProc, PunkTIFFCloseProc, PunkTIFFSizeProc, PunkTIFFMapFileProc, PunkTIFFUnmapFileProc)))
        {
            return false;
        }

        uint32 width;
        uint32 height;
        uint32 bps;
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);           // uint32 width;
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);        // uint32 height;
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);        // uint32 height;

        uint32 npixels = width * height;
        uint32* raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32));

        if (!TIFFReadRGBAImage(tif, width, height, raster, 0))
        {
            _TIFFfree(raster);
            return false;
        }

        image->Create(width, height, 4, ComponentType::UnsignedByte, ImageFormat::IMAGE_FORMAT_RGBA);
        memcpy(image->GetData(), raster, npixels*sizeof(uint32));

        _TIFFfree(raster);

        TIFFClose(tif);
        return true;
    }
}
#endif  /  /    USE_LIB_TIFF
