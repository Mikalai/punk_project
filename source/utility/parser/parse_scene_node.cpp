#include <memory>
#include "../../virtual/module.h"
#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseSceneNode(System::Buffer &buffer, Scene::Node *node)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw System::PunkInvalidArgumentException(L"Can't parse object");

            System::string word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NODE:
            {
                std::unique_ptr<Scene::Node> child(new Scene::Node);
                child->Graph(node->Graph());
                ParseSceneNode(buffer, child.get());
                node->Add(child.release());
            }
                break;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                node->Name(name);
            }
                break;
            case WORD_LOCATION:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                node->LocalPosition(value);
            }
                break;
            case WORD_ROTATION:
            {
                Math::quat value;
                ParseBlockedQuaternionf(buffer, value);
                node->LocalRotation(value);
            }
                break;
            case WORD_SCALE:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                node->LocalScale(value);
            }
                break;
            case WORD_ENTITY_NAME:
            {
                System::string value;
                ParseBlockedString(buffer, value);
                node->EntityName(value);
            }
                break;
            case WORD_BOUNDING_BOX:
            {
                Math::BoundingBox bbox;
                ParseBoundingBox(buffer, bbox);
                node->SetBoundingBox(bbox);
                node->SetBoundingSphere(bbox.ToBoundingSphere());
            }
                break;            
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
    }
}
