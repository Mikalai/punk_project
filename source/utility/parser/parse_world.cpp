#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseWorld(System::Buffer& buffer, Scene::SceneGraph* scene)
    {
        std::unique_ptr<Scene::Node> root(new Scene::Node);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                scene->SetRootNode(root.release());
                return true;
            case WORD_LOCATION_INDOOR:
            {
                std::unique_ptr<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
                ParseLocationIndoor(buffer, node.get());
                root->Add(node.release());
            }
                break;
            case WORD_TRANSFORM_NODE:
            {
                std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
                ParseTransformNode(buffer, node.get());
                root->Add(node.release());
            }
                break;
            case WORD_MATERIAL_NODE:
            {
                std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
                ParseMaterialNode(buffer, node.get());
                root->Add(node.release());
            }
                break;
            case WORD_MATERIALS:
            {
                ParseMaterials(buffer, scene);
            }
                break;
            case WORD_STATIC_MESHES:
            {
                ParseStaticMeshes(buffer);
            }
                break;
            case WORD_SKIN_MESHES:
            {
                ParseSkinMeshes(buffer);
            }
                break;
            case WORD_ACTIONS:
            {
                ParseActions(buffer);
            }
                break;
            case WORD_ARMATURES:
            {
                ParseArmatures(buffer);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        scene->SetRootNode(root.release());
        return true;
    }
}
