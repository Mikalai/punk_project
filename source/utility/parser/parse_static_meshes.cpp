#include "../../virtual/data/static_geometry.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseStaticMeshes(System::Buffer& buffer)
    {
        CHECK_START(buffer);

        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse object");

            System::string word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_STATIC_MESH:
            {
                std::unique_ptr<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
                ParseStaticMesh(buffer, mesh.get());
                Virtual::StaticGeometry::add(mesh->GetStorageName(), mesh.get());
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
