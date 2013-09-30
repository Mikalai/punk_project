#include "parse_functions.h"
#include "../../virtual/module.h"

namespace Utility
{
    bool ParseDirectionalLight(System::Buffer& buffer, Virtual::DirectionalLight* value)
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
            case WORD_ENERGY:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value->SetEnergy(v);
            }
                break;
            case WORD_COLOR:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value->SetColor(v);
            }
                break;
            case WORD_DIRECTION:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value->SetDirection(v);
            }
                break;
            case WORD_DISTANCE:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value->SetDistance(v);
            }
                break;
            default:
                return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
