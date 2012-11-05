#ifndef _H_PUNK_VIRTUAL_BASE_LOADER
#define _H_PUNK_VIRTUAL_BASE_LOADER

#include <vector>
#include "../../utility/model/vertex_bone_weight.h"
#include "../../virtual/animation/animation_track.h"
#include "keywords.h"

#define CHECK_START(buffer)\
	if (!CheckIntegrity(buffer))\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		return false;	\
		}

#define CHECK_END(buffer)\
	if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		return false;\
		}

namespace System
{
	class Buffer;
	class string;
}

namespace Math
{
	class vec2;
	class vec3;
	class vec4;
	class mat4;
	class BoundingBox;
}

namespace Utility
{
	class ObjectTypeDesc;
	class TextureMesh;
	class MeshDesc;
	class ObjectDesc;	
	class LightDesc;	
	class MaterialDesc;
	class ActionDesc;
	class AnimationDesc;
	class Frame;
	class BoneTrack;
	class ObjectTrack;
	class Camera;
	class WorldDesc;
	class ArmatureDesc;
	class BoneDesc;
	class CameraDesc;
}

namespace Utility
{
	class PUNK_ENGINE Parser
	{
	public:
		
		static bool LoadWorld(const	System::string& path, WorldDesc& world);

	private:

		static KeywordCode Parse(System::string& word);
		static bool CheckIntegrity(System::Buffer& buffer);

		//
		//	simple stuff
		//
		static bool ParseFloat(System::Buffer& buffer, float& value);
		static bool ParseInteger(System::Buffer& buffer, int& value);
		static bool ParseVector2f(System::Buffer& buffer, Math::vec2& value);
		static bool ParseVector3f(System::Buffer& buffer, Math::vec3& value);
		static bool ParseVector4f(System::Buffer& buffer, Math::vec4& value);
		static bool ParseVector2i(System::Buffer& buffer, Math::ivec2& value);
		static bool ParseVector3i(System::Buffer& buffer, Math::ivec3& value);
		static bool ParseVector4i(System::Buffer& buffer, Math::ivec4& value);
		static bool ParseMatrix4x4f(System::Buffer& buffer, Math::mat4& value);
		static bool ParseString(System::Buffer& buffer, System::string& value);

		//
		//	data blocks
		//
		static bool ParseBoundingBox(System::Buffer& buffer, Math::BoundingBox& value);
		static bool ParseBlockedString(System::Buffer& buffer, System::string& value);	
		static bool ParseBlockedVector3f(System::Buffer& buffer, Math::vec3& value);
		static bool ParseBlockedMatrix4x4f(System::Buffer& buffer, Math::mat4& value);
		static bool ParseBlockedFloat(System::Buffer& buffer, float& value);
		static bool ParseSubtype(System::Buffer& buffer, ObjectTypeDesc& value);	

		static bool ParseVector4iv(System::Buffer& buffer, std::vector<Math::ivec4>& value);
		static bool ParseVector3fv(System::Buffer& Buffer, std::vector<Math::vec3>& value);
		static bool ParseVector3iv(System::Buffer& Buffer, std::vector<Math::ivec3>& value);

		//	used for mesh texture coordinates
		static bool ParseVector4Vector2iv(System::Buffer& buffer, std::vector<Math::Vector4<Math::vec2>>& value);
		static bool ParseBonesWeights(System::Buffer& buffer, Virtual::VertexBoneWeights& value);
		

		//
		//	parse complex blocks
		//
		static bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value);		

		static bool ParseMesh(System::Buffer& buffer, MeshDesc& value);
		static bool ParseObject(System::Buffer& buffer, ObjectDesc& value);
		static bool ParseLight(System::Buffer& buffer, LightDesc& value);
		static bool ParseMaterials(System::Buffer& buffer, std::map<System::string, MaterialDesc*>& value);
		static bool ParseMaterial(System::Buffer& buffer, MaterialDesc& value);
		static bool ParseAction(System::Buffer& buffer, ActionDesc& value);
		static bool ParseActions(System::Buffer& buffer, std::map<System::string, ActionDesc*>& value);
		static bool ParseAnimation(System::Buffer& buffer, AnimationDesc& value);
		static bool ParseActionsRef(System::Buffer& buffer, std::vector<System::string>& value);
		//static bool ParseFrame(System::Buffer& buffer, Frame& value);
		//static bool ParseBoneTrack(System::Buffer& buffer, BoneTrack& value);
		static bool ParseObjectTrack(System::Buffer& buffer, ObjectTrack& value);
		static bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& value);
		static bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& value);
		static bool ParseCamera(System::Buffer&, CameraDesc& value);
		static bool ParseCollisionMesh(System::Buffer& buffer, Utility::MeshDesc& value);

		static bool ParseArmature(System::Buffer& buffer, ArmatureDesc& value);
		static bool ParseBone(System::Buffer& buffer, BoneDesc& value);
		static bool ParseWorld(System::Buffer& buffer, WorldDesc& value);		
	};
}

#endif