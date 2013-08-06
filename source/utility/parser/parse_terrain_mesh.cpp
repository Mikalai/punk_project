#include "parse_functions.h"
#include "../../virtual/module.h"

namespace Utility
{
    bool ParseTerrainMesh(System::Buffer& buffer, Virtual::TerrainMesh& value)
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
            default:
            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
