#include "../../scene/skin_mesh_node.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseSkinMeshNode(System::Buffer& buffer, Scene::SkinMeshNode* mesh)
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
                System::string value;
                ParseBlockedString(buffer, value);
                mesh->SetName(value);
                mesh->SetStorageName(value + L".skin");
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

}
