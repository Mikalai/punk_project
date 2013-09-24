#include "../../virtual/skinning/module.h"
#include "../../system/buffer.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone)
    {
        CHECK_START(buffer);
        System::string name, parent;
        while (1)
        {
            const System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string name;
                if (!ParseBlockedString(buffer, name))
                    return (out_error() << "Unable to parse bone name" << std::endl, false);
                bone->SetName(name);
            }
                break;
            case WORD_PARENT:
            {
                System::string name;
                if (!ParseBlockedString(buffer, name))
                    return (out_error() << "Unable to parse bone parent name" << std::endl, false);
                bone->SetParentName(name);
            }
                break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                if (!ParseBlockedMatrix4x4f(buffer, m))
                    return (out_error() << "Unable to parse bone local matrix" << std::endl, false);
                bone->SetLocalMatrix(m);
            }
                break;
            case WORD_BONE_MATRIX:
            {
                Math::mat4 m;
                if (!ParseBlockedMatrix4x4f(buffer, m))
                    return (out_error() << "Unable to parse bone local matrix" << std::endl, false);
                //bone->SetBoneMatrix(m);
            }
                break;
            case WORD_LENGTH:
            {
                float l;
                if (!ParseBlockedFloat(buffer, l))
                    return (out_error() << "Unable to parse bone length" << std::endl, false);
                bone->SetLength(l);
            }
                break;
            default:
                return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
