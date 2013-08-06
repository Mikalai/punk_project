#include "parse_functions.h"
#include "../../virtual/module.h"

namespace Utility
{
    bool ParseRiver(System::Buffer &buffer, Virtual::River &value)
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
            case WORD_MESH:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                value.SetStaticMeshFilename(name);
            }
            break;
            case WORD_FLOW_SPEED:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.SetFlowSpeed(v);
            }
            break;
            case WORD_FLOW_DIRECTION:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value.SetFlowDirection(v);
            }
            break;
            default:
            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}

