#ifndef PARSE_FUNCTIONS_H
#define PARSE_FUNCTIONS_H

#include <map>
#include <vector>

#include "../../system/errors/module.h"
#include "../../string/string.h"
#include "../../scene/interface.h"
#include "../../virtual/interface.h"
#include "../../math/vec4.h"
#include "../../math/vec2.h"
#include "../../math/mat4.h"
#include "../../math/quat.h"

#include "keywords.h"

#define CHECK_START(buffer)\
    if (!Utility::CheckIntegrity(buffer))\
{\
    throw System::PunkInvalidArgumentException(L"Integrity check failed");\
    }

#define CHECK_END(buffer)\
    if (Utility::Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
{\
    throw System::PunkInvalidArgumentException(L"Integrity check failed");\
    }

namespace Scene
{
    class SceneGraph;
}

namespace System
{
    class Buffer;
    class Object;
}

namespace Math
{
    class Spline;
    class WeightedPoint;
}

namespace AI
{
    class NaviMesh;
    class CurvePath;
}

namespace Utility
{
    extern KeywordCode Parse(const System::string& word);
    extern bool CheckIntegrity(System::Buffer& buffer);
    extern bool ParseFloat(System::Buffer& buffer, float& value);
    extern bool ParseInteger(System::Buffer& buffer, int& value);
    extern bool ParseVector2f(System::Buffer& buffer, Math::vec2& value);
    extern bool ParseVector3f(System::Buffer& buffer, Math::vec3& value);
    extern bool ParseVector4f(System::Buffer& buffer, Math::vec4& value);
    extern bool ParseVector2i(System::Buffer& buffer, Math::ivec2& value);
    extern bool ParseVector3i(System::Buffer& buffer, Math::ivec3& value);
    extern bool ParseVector4i(System::Buffer& buffer, Math::ivec4& value);
    extern bool ParseMatrix4x4f(System::Buffer& buffer, Math::mat4& value);
    extern bool ParseString(System::Buffer& buffer, System::string& value);
    extern bool ParseBlockedString(System::Buffer& buffer, System::string& value);
    extern bool ParseBlockedFloat(System::Buffer& buffer, float& value);
    extern bool ParseBlockedInteger(System::Buffer& buffer, int& value);
    extern bool ParseBlockedVector3f(System::Buffer& buffer, Math::vec3& value);
    extern bool ParseBlockedVector4f(System::Buffer& buffer, Math::vec4& value);
    extern bool ParseBlockedVector2i(System::Buffer& buffer, Math::ivec2& value);
    extern bool ParseBlockedVector2f(System::Buffer& buffer, Math::vec2& value);
    extern bool ParseBlockedMatrix4x4f(System::Buffer& buffer, Math::mat4& value);
    extern bool ParseVector3fv(System::Buffer& buffer, std::vector<Math::vec3>& value);
    extern bool ParseVector3iv(System::Buffer& buffer, std::vector<Math::ivec3>& value);
    extern bool ParseVector4iv(System::Buffer& buffer, std::vector<Math::ivec4>& value);
    extern bool ParseVector4Vector2iv(System::Buffer& buffer, std::vector<Math::Vector4<Math::vec2>>& value);
    extern bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value);
    extern bool ParseBonesWeights(System::Buffer& buffer, std::map<int, std::map<System::string, float>>& value);
    extern bool ParseWorld(System::Buffer& buffer, Scene::SceneGraph* scene);    
    extern bool ParseMaterials(System::Buffer& buffer, Scene::SceneGraph* scene);
    extern bool ParseMaterial(System::Buffer& buffer, Virtual::Material* mat);
    extern bool ParseStaticMeshes(System::Buffer& buffer);
    extern bool ParseStaticMesh(System::Buffer& buffer, Virtual::StaticGeometry* geometry);    
    extern bool ParseSkinMeshes(System::Buffer& buffer);
    extern bool ParseSkinMesh(System::Buffer& buffer, Virtual::SkinGeometry* geometry);    
    extern bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone);
    extern bool ParseArmature(System::Buffer& buffer, Virtual::Armature* armature);
    extern bool ParseArmatures(System::Buffer& buffer);    
    extern bool ParseActions(System::Buffer& buffer);
    extern bool ParseAction(System::Buffer& buffer, Virtual::Action* action);
    extern bool ParseAnimation(System::Buffer& buffer, Virtual::Animation* animation);
    extern bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& track);
    extern bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& track);    
    extern bool ParseMapDescription(System::Buffer& buffer, Virtual::Terrain* terrain);
    extern bool ParseConvexMesh(System::Buffer& buffer, Math::ConvexShapeMesh& mesh);
    extern bool ParseTerrainRawDataSource(System::Buffer& buffer, Virtual::TerrainRawDataSource& source);
    extern bool ParseTerrainCell(System::Buffer& buffer, Virtual::TerrainCell& cell);
    extern bool ParseBoundingBox(System::Buffer& buffer, Math::BoundingBox& value);
    extern System::Object* ParseAnything(System::Buffer& buffer);
    extern bool ParseNaviMesh(System::Buffer& buffer, AI::NaviMesh* value);
    extern bool ParseCurvePath(System::Buffer& buffer, AI::CurvePath* value);
    extern bool ParseSpline(System::Buffer& buffer, Math::Spline& value);
    extern bool ParseWeightedPoint(System::Buffer& buffer, Math::WeightedPoint& value);
    PUNK_ENGINE_LOCAL bool ParseTextureSlot(System::Buffer& buffer, Virtual::TextureSlot& value);
    PUNK_ENGINE_LOCAL bool ParseSceneGraph(System::Buffer& buffer, Scene::SceneGraph& value);
    PUNK_ENGINE_LOCAL bool ParseSun(System::Buffer& buffer, Virtual::Sun& value);
    PUNK_ENGINE_LOCAL bool ParseTerrainMesh(System::Buffer& buffer, Virtual::TerrainMesh& value);
    PUNK_ENGINE_LOCAL bool ParseRiver(System::Buffer& buffer, Virtual::River& value);
    PUNK_ENGINE_LOCAL bool ParseSceneNode(System::Buffer& buffer, Scene::Node* node);
    PUNK_ENGINE_LOCAL bool ParseLocationIndoor(System::Buffer& buffer, Scene::Node* location);
    PUNK_ENGINE_LOCAL bool ParsePortalNode(System::Buffer& buffer, Scene::Node* node);
    PUNK_ENGINE_LOCAL bool ParseTransformNode(System::Buffer& buffer, Scene::Node* transform);
    PUNK_ENGINE_LOCAL bool ParseMaterialNode(System::Buffer& buffer, Scene::Node* material);
    PUNK_ENGINE_LOCAL bool ParsePointLightNode(System::Buffer& buffer, Scene::Node* value);
    PUNK_ENGINE_LOCAL bool ParseStaticMeshNode(System::Buffer& buffer, Scene::Node* static_node);
    PUNK_ENGINE_LOCAL bool ParseSkinMeshNode(System::Buffer& buffer, Scene::Node* skin_node);
    PUNK_ENGINE_LOCAL bool ParseArmatureNode(System::Buffer& buffer, Scene::Node* armature_node);
    PUNK_ENGINE_LOCAL bool ParseBoneNode(System::Buffer& buffer, Scene::Node* node);
    PUNK_ENGINE_LOCAL bool ParseSunNode(System::Buffer& buffer, Scene::Node& value);
    PUNK_ENGINE_LOCAL bool ParseNaviMeshNode(System::Buffer& buffer, Scene::Node& value);
    PUNK_ENGINE_LOCAL bool ParsePathNode(System::Buffer& buffer, Scene::Node& value);
    PUNK_ENGINE_LOCAL bool ParseTerrainNode(System::Buffer& buffer, Scene::Node& value);
    PUNK_ENGINE_LOCAL bool ParseRiverNode(System::Buffer& buffer, Scene::Node& value);
}

#endif // PARSE_FUNCTIONS_H
