#include "parse_functions.h"
#include "../../system/buffer.h"
#include "../../string/string.h"

namespace Utility
{
    bool ParseBonesWeights(System::Buffer& buffer, std::map<int, std::map<System::string, float>>& value)
    {
        CHECK_START(buffer);

        while (1)
        {
            System::string word = buffer.ReadWord();
            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;
            int vertex_id = word.ToInt32();
            System::string bone_name = buffer.ReadWord();
            float weight = buffer.ReadWord().ToFloat();
            value[vertex_id][bone_name] = weight;
        }
        throw System::PunkInvalidArgumentException(L"Unable to parse vertex bones weights");
    }
}
