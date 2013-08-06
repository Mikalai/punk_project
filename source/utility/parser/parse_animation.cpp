#include "../../virtual/animation/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseAnimation(System::Buffer& buffer, Virtual::Animation* animation)
    {
        CHECK_START(buffer);

        System::string name;

        while (1)
        {
            if (buffer.IsEnd())
            {
                throw System::PunkInvalidArgumentException(L"Can't parse object");
            }

            const System::string word = buffer.ReadWord();
            KeywordCode index = Parse(word);
            switch(index)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                animation->SetName(name);
            }
                break;
            case WORD_POSITION_TRACK:
            {
                Virtual::AnimationTrack<Math::vec3> track;
                ParsePositionTrack(buffer, track);
                animation->SetPositionTrack(track);
            }
                break;
            case WORD_ROTATION_TRACK:
            {
                Virtual::AnimationTrack<Math::quat> track;
                ParseRotationTrack(buffer, track);
                animation->SetRotationTrack(track);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
