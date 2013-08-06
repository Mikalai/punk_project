#include "../../virtual/data/static_geometry.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseStaticMesh(System::Buffer& buffer, Virtual::StaticGeometry* geometry)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse object");

            System::string word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                geometry->SetName(name);                
            }
                break;
            case WORD_VERTEX_POSITION:
            {
                Virtual::StaticGeometry::Vertices v;
                ParseVector3fv(buffer, v);
                geometry->SetVertices(v);
            }
                break;
            case WORD_NORMALS:
            {
                Virtual::StaticGeometry::Normals n;
                ParseVector3fv(buffer, n);
                geometry->SetNormals(n);
            }
                break;
            case WORD_FACES:
            {
                Virtual::StaticGeometry::Faces f;
                ParseVector3iv(buffer, f);
                geometry->SetFaces(f);
            }
                break;
            case WORD_TEXTURE:
            {
                Virtual::StaticGeometry::TextureMeshes t;
                ParseTextures(buffer, t);
                geometry->SetTextureMeshes(t);
            }
                break;
            case WORD_WORLD_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                geometry->SetWorldOffset(m);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
    }
}
