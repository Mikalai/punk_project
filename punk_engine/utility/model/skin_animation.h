#ifndef _H_PUNK_SKIN
#define _H_PUNK_SKIN

#include "../config.h"
#include <vector>
#include <map>
#include "../../math/header_matrix.h"
#include "../../math/mat4.h"
#include "../../math/quat.h"
#include "bone.h"
#include "bone_frame.h"
#include "armature.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;
	
	struct Frame
	{
		Math::quat m_rotation;
		Math::vec3 m_position;
	};

	class LIB_UTILITY SkinAnimation
	{	
		System::string m_name;
		Armature* m_rest_pose;
		Math::mat4 m_mesh_offset;

		float m_duration;
		float m_tick_per_second;
		
		typedef std::map<FrameID, std::map<BoneName, Frame>> Type;
		Type m_animation;

	public:
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

		int GetBonesCount() const;

		const Math::quat GetRotation(unsigned bone_id, unsigned frame) const;
		const Math::quat GetRotation(const BoneName& bone, unsigned frame) const;
		const Math::vec3 GetPosition(unsigned bone_id, unsigned frame) const;
		const Math::vec3 GetPosition(const BoneName& bone, unsigned frame) const;
		const Math::mat4 GetTransform(unsigned bone_id, unsigned frame) const;
		const Math::mat4 GetTransform(const BoneName& bone, unsigned frame) const;
		const Math::mat4 GetMeshOffset() const;

		const Math::mat4 GetInterpolatedTransform(unsigned bone_id, unsigned frame1, unsigned frame2, float t) const;
		const Math::mat4 GetInterpolatedTransform(const BoneName& bone, unsigned frame1, unsigned frame2, float t) const;

		unsigned GetFramesCount() const;
		const Armature& GetRestPosition() const;
		float GetDuration() const;
		float GetTicksPerSecond() const;
		const System::string GetName() const;

		const Bone& GetBone(unsigned id) const;

		void SetDuration(float duration);
		void SetTicksPerSecond(float tps);
		void SetRestPosition(Armature* skeleton);		
		void SetRotation(const Math::quat& rot, unsigned bone_id, unsigned frame);
		void SetRotation(const Math::quat& rot, const BoneName& bone, unsigned frame);
		void SetPosition(const Math::vec3& pos, unsigned bone_id, unsigned frame);
		void SetPosition(const Math::vec3& pos, const BoneName& bone, unsigned frame);		
		void SetName(const System::string& name);
		void SetMeshOffset(const Math::mat4& mat);

		void SetAnimationSize(unsigned bones_count, unsigned frame_count);
		Frame& GetFrame(const BoneName& bone, const FrameID& frame);
		const Frame& GetFrame(const BoneName& bone, const FrameID& frame) const;

		Type& GetAnimation();
		const Type& GetAnimation() const;

		friend class RawScene;
	};
}

#endif