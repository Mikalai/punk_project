#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParsePortalNode(System::Buffer& buffer, Scene::PortalNode* node)
    {
        CHECK_START(buffer);

        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch (Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                node->SetName(name);
                node->SetStorageName(name);
            }
                break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                node->SetLocalMatrix(m);
            }
                break;
            case WORD_VERTEX_POSITION:
            {
                Math::Portal::PointsCollection p;
                ParseVector3fv(buffer, p);
                Math::Portal portal;
                portal.SetPoints(p);
                node->SetPortal(portal);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
