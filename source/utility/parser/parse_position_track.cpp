#include "../../virtual/animation/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            System::string word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int frame = word.ToInt32();
            float x = buffer.ReadWord().ToFloat();
            float y = buffer.ReadWord().ToFloat();
            float z = buffer.ReadWord().ToFloat();

            Math::vec3 v;
            v.Set(x,y,z);

            value.AddKey(frame, v);
        }
        throw System::PunkInvalidArgumentException(L"Unable to parse position track");
    }
}
