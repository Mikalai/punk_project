
//#include <memory>
//#include "../../virtual/module.h"
//#include "../../scene/module.h"
//#include "parse_functions.h"

//namespace Utility
//{
//    bool ParseSceneTransformNode(System::Buffer &buffer, Scene::TransformNode *node)
//    {
//        CHECK_START(buffer);
//        while (1)
//        {
//            if (buffer.IsEnd())
//                throw System::PunkInvalidArgumentException(L"Can't parse object");

//            System::string word = buffer.ReadWord();

//            KeywordCode code = Parse(word);
//            switch(code)
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NODE:
//            {
//                std::unique_ptr<Scene::TransformNode> child(new Scene::TransformNode);
//                ParseSceneTransformNode(buffer, child.get());
//                node->Add(child.release());
//            }
//                break;
//            case WORD_NAME:
//            {
//                System::string name;
//                ParseBlockedString(buffer, name);
//                node->Name(name);
//            }
//                break;
//            case WORD_LOCATION:
//            {
//                Math::vec3 value;
//                ParseBlockedVector3f(buffer, value);
//                node->Position(value);
//            }
//                break;
//            case WORD_ROTATION:
//            {
//                Math::quat value;
//                ParseBlockedQuaternionf(buffer, value);
//                node->Rotation(value);
//            }
//                break;
//            case WORD_SCALE:
//            {
//                Math::vec3 value;
//                ParseBlockedVector3f(buffer, value);
//                node->Scale(value);
//            }
//                break;
//            case WORD_ENTITY_NAME:
//            {
//                System::string value;
//                ParseBlockedString(buffer, value);
//                node->EntityName(value);
//            }
//                break;
//            case WORD_BOUNDING_BOX:
//            {
//                Math::BoundingBox bbox;
//                ParseBoundingBox(buffer, bbox);
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//    }
//}
