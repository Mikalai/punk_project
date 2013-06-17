#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseStaticMeshNode(System::Buffer& buffer, Scene::StaticMeshNode* mesh)
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
                mesh->SetStorageName(value);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
