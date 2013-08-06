#include "../../virtual/skinning/module.h"
#include "../../virtual/data/skin_geometry.h"

#include "parse_functions.h"

namespace Utility
{
    bool ParseSkinMeshes(System::Buffer& buffer)
    {
        CHECK_START(buffer);
        System::string name;
        while (1)
        {
            System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_SKIN_MESH:
            {
                std::unique_ptr<Virtual::SkinGeometry> mesh(new Virtual::SkinGeometry);
                ParseSkinMesh(buffer, mesh.get());                
                mesh.release();
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
