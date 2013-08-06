#include "parse_functions.h"
#include "../../system/buffer.h"
#include "../../math/convex_shape_mesh.h"

namespace Utility
{
    bool ParseConvexMesh(System::Buffer& buffer, Math::ConvexShapeMesh& mesh)
    {
        CHECK_START(buffer);

        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse convex mesh");

            System::string s = buffer.ReadWord();
            KeywordCode index = Parse(s);
            switch (index)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_VERTEX_POSITION:
            {
                Math::ConvexShapeMesh::PointsCollection p;
                ParseVector3fv(buffer, p);
                mesh.SetPoints(p);
            }
                break;
            case WORD_FACES:
            {
                Math::ConvexShapeMesh::FacesCollection f;
                ParseVector3iv(buffer, f);
                mesh.SetFaces(f);
            }
                break;
            case WORD_FACE_NORMALS:
            {
                Math::ConvexShapeMesh::NormalsCollection n;
                ParseVector3fv(buffer, n);
                mesh.SetNormals(n);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected word " + s);
            }
        }
    }
}
