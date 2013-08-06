#include "parse_functions.h"
#include "../../ai/module.h"

namespace Utility
{
    bool ParseNaviMesh(System::Buffer &buffer, AI::NaviMesh* value)
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
            {
                return true;
            }
            case WORD_WORLD_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                value->SetTransform(m);
            }
            break;
            case WORD_VERTEX_POSITION:
            {
                AI::NaviMesh::Points v;
                ParseVector3fv(buffer, v);
                value->SetPoints(v);
            }
            break;
            case WORD_NORMALS:
            {
                AI::NaviMesh::Normals v;
                ParseVector3fv(buffer, v);
                value->SetNormals(v);
            }
            break;
            case WORD_FACES:
            {
                AI::NaviMesh::Faces f;
                ParseVector3iv(buffer, f);
                value->SetFaces(f);
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
