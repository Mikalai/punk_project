#include "../system/environment.h"
#include "../system/errors/module.h"
#include "path_finder.h"

namespace Utility
{
    const System::string FindPath(const System::string &filename)
    {
        if (filename.EndWith(L".static")
                || filename.EndWith(L".skin")
                || filename.EndWith(L".river")
                || filename.EndWith(L".terrain")
                || filename.EndWith(L".material")
                || filename.EndWith(L".sun")
                || filename.EndWith(L".pmd")
                || filename.EndWith(L"armature")
                || filename.EndWith(L".action")
                || filename.EndWith(L".path")
                || filename.EndWith(L".navi_mesh")
                || filename.EndWith(L".dir_lamp")
                || filename.EndWith(L".point_lamp")
                || filename.EndWith(L".spot_lamp"))
            return System::Environment::Instance()->GetModelFolder() + filename;

        if (filename.EndWith(L".jpg")
                || filename.EndWith(L".png")
                || filename.EndWith(L".tif"))
            return System::Environment::Instance()->GetTextureFolder() + filename;
        throw System::PunkException(L"Can't locate resource file: " + filename);
    }
}
