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
                ParseSceneNode(buffer, child.get());
                node->Add(child.release());
            }
                break;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                node->SetName(name);
            }
                break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                std::unique_ptr<Virtual::Transform> t(new Virtual::Transform);
                t->Set(m);
                node->SetData(t.release());
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
