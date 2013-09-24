#include "parse_functions.h"

namespace Utility
{

    bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<std::array<Math::vec2, 4>>>& value)
    {
        CHECK_START(buffer);

        System::string name;

        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse object");

            System::string s = buffer.ReadWord();

            switch(KeywordCode index = Parse(s))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                ParseBlockedString(buffer, name);
            }
                break;
            case WORD_TEXTURE_COORD:
            {
                ParseVector4Vector2iv(buffer, value[name]);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(System::string("Unexpected keyword {0}").arg(Keyword[index].word));
            }
        }
        return true;
    }

}
