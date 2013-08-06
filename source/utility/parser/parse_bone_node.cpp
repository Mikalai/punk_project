#include "../../scene/transform_node.h"
#include "../../scene/bone_node.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseBoneNode(System::Buffer& buffer, Scene::BoneNode* bone)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch (Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                System::string value;
                ParseBlockedString(buffer, value);
                bone->SetName(value);
                bone->SetStorageName(value);
            }
                break;
            case WORD_TRANSFORM_NODE:
            {
                std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
                ParseTransformNode(buffer, node.get());
                bone->Add(node.release());
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

}
