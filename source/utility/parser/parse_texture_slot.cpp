#include "parse_functions.h"
#include "../../virtual/module.h"

namespace Utility
{
    bool ParseTextureSlot(System::Buffer& buffer, Virtual::TextureSlot& value)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_SCALE:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value.SetScale(v);
            }
            break;
            case WORD_IMAGE:
            {
                System::string v;
                ParseBlockedString(buffer, v);
                value.SetFilename(v);
            }
            break;
            case WORD_SPECULAR_INTENSITY_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsSpecularIntensityMapSlot(true);
                value.SetSpecularIntensityFactor(v);
            }
            break;
            case WORD_DIFFUSE_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsDiffuseMapSlot(true);
                value.SetDiffuseFactor(v);
            }
            break;
            case  WORD_NORMAL_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsNormalMapSlot(true);
                value.SetNormalFactor(v);
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
