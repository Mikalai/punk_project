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
            case WORD_NODE:
            {
                std::unique_ptr<Scene::Node> node(new Scene::Node);
                node->Graph(&value);
                ParseSceneNode(buffer, node.get());
                value.Add(node.release());
            }
            break;            
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
    }
}
