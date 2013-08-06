#include "../../ai/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseWeightedPoint(System::Buffer &buffer, Math::WeightedPoint& value)
    {
        CHECK_START(buffer);
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
            case WORD_WEIGHT:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.SetWeight(v);
            }
            break;
            case WORD_POSITION:
            {
                Math::vec4 v;
                ParseBlockedVector4f(buffer, v);
                value.SetPoint(v);
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
