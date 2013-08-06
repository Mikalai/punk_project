#include "../../ai/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseCurvePath(System::Buffer &buffer, AI::CurvePath *value)
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
            case WORD_SPLINE:
            {
                Math::Spline spline;
                ParseSpline(buffer, spline);
                value->AddSpline(spline);
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
