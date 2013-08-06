#include "parse_functions.h"
#include "../../scene/module.h"

namespace Utility
{
    bool ParseNaviMeshNode(System::Buffer& buffer, Scene::NaviMeshNode& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            const System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                value.SetName(name);
                value.SetStorageName(name + L".navi_mesh");
            }
            break;
            default:
            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
