#include "../../ai/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseSpline(System::Buffer &buffer, Math::Spline &value)
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
            case WORD_POINT:
            {
                Math::WeightedPoint p;
                ParseWeightedPoint(buffer, p);
                value.AddPoint(p);
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}

