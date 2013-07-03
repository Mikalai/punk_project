#include "parse_functions.h"
#include "../../scene/module.h"

namespace Utility
{

    bool ParseSunNode(System::Buffer &buffer, Scene::SunNode &value)
    {
        CHECK_START(buffer);
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
                ParseBlockedString(buffer, name);
                value.SetName(name);
                value.SetStorageName(name + L".sun");
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
            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
            }
        }
        return false;
    }
}
