#include "../../virtual/animation/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            System::string word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int frame = word.ToInt32();
            float w = buffer.ReadWord().ToFloat();
            float x = buffer.ReadWord().ToFloat();
            float y = buffer.ReadWord().ToFloat();
            float z = buffer.ReadWord().ToFloat();

            Math::Quaternion<float> v;
            v.Set(w,x,y,z);

            value.AddKey(frame, v);
        }
        throw System::PunkInvalidArgumentException(L"Unable to parse rotation track");
    }
}
