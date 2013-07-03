#include "../../system/buffer.h"
#include "../../scene/module.h"
#include "parse_functions.h"


namespace Utility
{
    bool ParseSceneGraph(System::Buffer& buffer, Scene::SceneGraph& value)
    {
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_LOCATION_INDOOR:
            {
                std::unique_ptr<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
                ParseLocationIndoor(buffer, node.get());
                value.Add(node.release());
            }
            break;
            case WORD_TRANSFORM_NODE:
            {
                std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
                ParseTransformNode(buffer, node.get());
                value.Add(node.release());
            }
            break;
            case WORD_MATERIAL_NODE:
            {
                std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
                ParseMaterialNode(buffer, node.get());
                value.Add(node.release());
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
    }
}
