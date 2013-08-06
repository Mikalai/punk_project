#include "../../scene/module.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseTransformNode(System::Buffer& buffer, Scene::TransformNode* transform)
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
                transform->SetName(value);
                transform->SetStorageName(value);
            }
            break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                transform->SetLocalMatrix(m);
            }
            break;
            case WORD_POINT_LIGHT:
            {
                std::unique_ptr<Scene::PointLightNode> node(new Scene::PointLightNode);
                ParsePointLightNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_STATIC_MESH_NODE:
            {
                std::unique_ptr<Scene::StaticMeshNode> node(new Scene::StaticMeshNode);
                ParseStaticMeshNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_SKIN_MESH_NODE:
            {
                std::unique_ptr<Scene::SkinMeshNode> node(new Scene::SkinMeshNode);
                ParseSkinMeshNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_ARMATURE_NODE:
            {
                std::unique_ptr<Scene::ArmatureNode> node(new Scene::ArmatureNode);
                ParseArmatureNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_MATERIAL_NODE:
            {
                std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
                ParseMaterialNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_TRANSFORM_NODE:
            {
                std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
                ParseTransformNode(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_LOCATION_INDOOR:
            {
                std::unique_ptr<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
                ParseLocationIndoor(buffer, node.get());
                transform->Add(node.release());
            }
            break;
            case WORD_BOUNDING_BOX:
            {
                Math::BoundingBox bbox;
                ParseBoundingBox(buffer, bbox);
                transform->SetBoundingBox(bbox);
            }
            break;
            case WORD_SUN_NODE:
            {
                std::unique_ptr<Scene::SunNode> node(new Scene::SunNode);
                ParseSunNode(buffer, *node);
                transform->Add(node.release());
            }
            break;
            case WORD_PATH_NODE:
            {
                std::unique_ptr<Scene::PathNode> node(new Scene::PathNode);
                ParsePathNode(buffer, *node);
                transform->Add(node.release());
            }
            break;
            case WORD_NAVIMESH_NODE:
            {
                std::unique_ptr<Scene::NaviMeshNode> node(new Scene::NaviMeshNode);
                ParseNaviMeshNode(buffer, *node);
                transform->Add(node.release());
            }
            break;
            case WORD_TERRAIN_NODE:
            {
                std::unique_ptr<Scene::TerrainNode> node(new Scene::TerrainNode);
                ParseTerrainNode(buffer, *node);
                transform->Add(node.release());
            }
            break;
            case WORD_RIVER_NODE:
            {
                std::unique_ptr<Scene::RiverNode> node(new Scene::RiverNode);
                ParseRiverNode(buffer, *node);
                transform->Add(node.release());
            }
            break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
