#ifndef OPENEXR_IMPORTER_H
#define OPENEXR_IMPORTER_H

#include "importer.h"

#ifdef USE_OPENEXR
//#include <OpenEXR/Iex.h>
#endif

namespace ImageModule
{

class OpenEXRImporter : public Importer
{
public:
    OpenEXRImporter();
};

}

#endif // OPENEXR_IMPORTER_H
