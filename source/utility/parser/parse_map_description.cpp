#include "../../virtual/terrain/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseMapDescription(System::Buffer& buffer, Virtual::Terrain* terrain)
    {
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NUM_BLOCKS:
            {
                int value;
                ParseBlockedInteger(buffer, value);
                terrain->SetNumBlocks(value);
            }
                break;
            case WORD_BLOCK_SCALE:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                terrain->SetBlockScale(value);
            }
                break;
            case WORD_BLOCK_SIZE:
            {
                int value;
                ParseBlockedInteger(buffer, value);
                terrain->SetBlocksSize(value);
            }
                break;
            case WORD_HEIGHT_SCALE:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                terrain->SetHeightScale(value);
            }
                break;
            case WORD_WORLD_ORIGIN:
            {
                Math::vec2 value;
                ParseBlockedVector2f(buffer, value);
                terrain->SetOrigin(value);
            }
                break;
            case WORD_CELL:
            {
                Virtual::TerrainCell value;
                ParseTerrainCell(buffer, value);
                value.Validate();
                terrain->AddOrUpdateCell(value);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return true;
    }
}
