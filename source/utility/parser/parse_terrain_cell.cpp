#include "../../virtual/terrain/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseTerrainCell(System::Buffer& buffer, Virtual::TerrainCell& cell)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string value;
                ParseBlockedString(buffer, value);
                cell.SetName(value);
            }
                break;
            case WORD_LOCATION:
            {
                Math::ivec2 value;
                ParseBlockedVector2i(buffer, value);
                cell.SetLocation(value);
            }
                break;
            case WORD_RAW_DATA_SOURCE:
            {
                Virtual::TerrainRawDataSource value;
                ParseTerrainRawDataSource(buffer, value);
                cell.SetRawDataSource(value);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
