#include "../../virtual/terrain/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseTerrainRawDataSource(System::Buffer& buffer, Virtual::TerrainRawDataSource& source)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_REF:
            {
                System::string value;
                ParseBlockedString(buffer, value);
                source.SetRawFile(value);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
