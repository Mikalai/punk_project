#include "../../virtual/animation/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseAction(System::Buffer& buffer, Virtual::Action* action)
    {
        CHECK_START(buffer);

        System::string name;

        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse action");

            const System::string word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string value;
                ParseBlockedString(buffer, value);
                action->SetName(value);
            }
                break;
            case WORD_TIMING:
            {
                CHECK_START(buffer);
                action->SetStartFrame(buffer.ReadWord().ToInt32());
                action->SetEndFrame(buffer.ReadWord().ToInt32());
                if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)
                    throw System::PunkInvalidArgumentException(L"Can't parse action timing");
            }
                break;
            case WORD_BONE_ANIMATION:
            {
                std::unique_ptr<Virtual::BoneAnimation> animation(new Virtual::BoneAnimation);
                ParseAnimation(buffer, animation.get());
                action->Add(animation.release());
            }
                break;
            case WORD_OBJECT_ANIMATION:
            {
                std::unique_ptr<Virtual::ObjectAnimation> animation(new Virtual::ObjectAnimation);
                ParseAnimation(buffer, animation.get());
                action->Add(animation.release());
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
    }

    bool ParseActions(System::Buffer& buffer)
    {
        CHECK_START(buffer);

        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse object");

            System::string word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            default:
                return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }

}
