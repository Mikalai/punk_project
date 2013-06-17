#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseArmatureNode(System::Buffer& buffer, Scene::ArmatureNode* armature_node)
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
                armature_node->SetName(value);
                armature_node->SetStorageName(value);
            }
                break;
            case WORD_MATERIAL_NODE:
            {
                std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
                ParseMaterialNode(buffer, node.get());
                armature_node->Add(node.release());
            }
                break;
            case WORD_BONE_NODE:
            {
                std::unique_ptr<Scene::BoneNode> node(new Scene::BoneNode);
                ParseBoneNode(buffer, node.get());
                armature_node->Add(node.release());
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

}
