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
    extern bool ParseLocationIndoor(System::Buffer& buffer, Scene::LocationIndoorNode* location);
    extern bool ParsePortalNode(System::Buffer& buffer, Scene::PortalNode* node);
    extern bool ParseTransformNode(System::Buffer& buffer, Scene::TransformNode* transform);
    extern bool ParseMaterialNode(System::Buffer& buffer, Scene::MaterialNode* material);
    extern bool ParsePointLightNode(System::Buffer& buffer, Scene::PointLightNode* value);
    extern bool ParseMaterials(System::Buffer& buffer, Scene::SceneGraph* scene);
    extern bool ParseMaterial(System::Buffer& buffer, Virtual::Material* mat);
    extern bool ParseStaticMeshes(System::Buffer& buffer);
    extern bool ParseStaticMesh(System::Buffer& buffer, Virtual::StaticGeometry* geometry);
    extern bool ParseStaticMeshNode(System::Buffer& buffer, Scene::StaticMeshNode* static_node);
    extern bool ParseSkinMeshes(System::Buffer& buffer);
    extern bool ParseSkinMesh(System::Buffer& buffer, Virtual::SkinGeometry* geometry);
    extern bool ParseSkinMeshNode(System::Buffer& buffer, Scene::SkinMeshNode* skin_node);
    extern bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone);
    extern bool ParseArmature(System::Buffer& buffer, Virtual::Armature* armature);
    extern bool ParseArmatures(System::Buffer& buffer);
    extern bool ParseArmatureNode(System::Buffer& buffer, Scene::ArmatureNode* armature_node);
    extern bool ParseActions(System::Buffer& buffer);
    extern bool ParseAction(System::Buffer& buffer, Virtual::Action* action);
    extern bool ParseAnimation(System::Buffer& buffer, Virtual::Animation* animation);
    extern bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& track);
    extern bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& track);
    extern bool ParseBoneNode(System::Buffer& buffer, Scene::BoneNode* node);
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
}
#endif // PARSE_FUNCTIONS_H
