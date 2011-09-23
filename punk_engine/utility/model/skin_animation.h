#ifndef _H_PUNK_SKIN
#define _H_PUNK_SKIN

#include "../config.h"
#include <vector>
#include <map>
#include "../../math/smart_matrix.h"
#include "../../math/mat4.h"
#include "../../math/quat.h"
#include "scene.h"
#include "bone.h"
#include "skeleton.h"

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
		SkeletonID m_rest_pose;
		
		float m_duration;
		float m_tick_per_second;

		Math::Matrix<float> m_time;
		Math::Matrix<Frame> m_animation;

	public:
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

		int GetBonesCount() const;

		const Math::quat GetRotation(unsigned bone_id, unsigned frame) const;
		const Math::vec3 GetPosition(unsigned bone_id, unsigned frame) const;
		const Math::mat4 GetTransform(unsigned bone_id, unsigned frame) const;

		const Math::mat4 GetInterpolatedTransform(unsigned bone_id, unsigned frame1, unsigned frame2, float t) const;

		unsigned GetFramesCount() const;
		const SkeletonID& GetRestPosition() const;
		float GetDuration() const;
		float GetTicksPerSecond() const;
		const System::string GetName() const;

		const Bone& GetBone(unsigned id) const;

		void SetDuration(float duration);
		void SetTicksPerSecond(float tps);
		void SetRestPosition(SkeletonID& skeleton);
		void SetAnimationSize(unsigned bones_count, unsigned frame_count);
		void SetRotation(const Math::quat& rot, unsigned bone_id, unsigned frame);
		void SetPosition(const Math::vec3& pos, unsigned bone_id, unsigned frame);
		void SetFrameTimeValue(unsigned frame_id, float time);
		void SetName(const System::string& name);
		friend class RawScene;
	};
}

#endif