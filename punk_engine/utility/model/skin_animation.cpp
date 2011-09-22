#include <algorithm>
#include "skin_animation.h"
#include "../../system/system.h"
#include "../../math/math.h"

namespace Utility
{
	int SkinAnimation::GetBonesCount() const
	{
		return m_rest_pose.size();
	}

	unsigned SkinAnimation::GetFramesCount() const
	{
		return m_animation.ColumnCount();
	}

	const Math::quat SkinAnimation::GetRotation(unsigned int bone_id, unsigned int frame) const
	{
		int parent = m_animation.At(bone_id, frame).m_parent;
		Math::quat res = m_animation.At(bone_id, frame).m_rotation;
		if (parent == -1)
			return res;	
		return GetRotation(parent, frame)*res;
	}

	const Math::mat4 SkinAnimation::GetTransform(unsigned int bone_id, unsigned int frame) const
	{
		int parent = m_animation.At(bone_id, frame).m_parent;
		Math::quat res = m_animation.At(bone_id, frame).m_rotation;
		if (parent == -1)
			return res.ToMatrix4x4();	
		return GetTransform(parent, frame)*res.ToMatrix4x4();
	}


	const Math::vec3 SkinAnimation::GetPosition(unsigned int bone_id, unsigned int frame) const
	{
		int parent = m_animation.At(bone_id, frame).m_parent;
		Math::vec3 res = m_animation.At(bone_id, frame).m_position;
		if (parent == -1)
			return res;	
		return GetPosition(parent, frame)+res;
	}

	const Bone& SkinAnimation::GetBone(unsigned id) const
	{
		return m_rest_pose[id];
	}

	/*
	BoneFrame SkinAnimation::GetGlobal(int frame_index, int index)
	{
		BoneFrame m = m_animation.At(frame_index, index);
	//	m[12] = 0;
	//	m[13] = 0;
	//	m[14] = 0;
		return m;
	}

	int SkinAnimation::GetFramesCount() const
	{
		return m_frame_values.ColumnCount();
	}

	int SkinAnimation::GetBonesCount() const
	{
		return m_animation.ColumnCount();
	}*/
}