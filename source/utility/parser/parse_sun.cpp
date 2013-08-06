#include "parse_functions.h"
#include "../../virtual/data/module.h"

namespace Utility
{
    bool ParseSun(System::Buffer &buffer, Virtual::Sun &value)
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
                value.SetEnergy(v);
            }
            break;
            case WORD_COLOR:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value.SetColor(v);
            }
            break;
            default:
            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
