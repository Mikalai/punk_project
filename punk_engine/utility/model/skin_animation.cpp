#include <algorithm>
#include "bone.h"
#include "skin_animation.h"
#include "../../system/system.h"
#include "../../math/math.h"

namespace Utility
{
	int SkinAnimation::GetBonesCount() const
	{
		return m_rest_pose->GetBonesCount();
	}

	unsigned SkinAnimation::GetFramesCount() const
	{
		return m_animation.size();
	}

	const Math::quat SkinAnimation::GetRotation(unsigned int bone_id, unsigned int frame) const
	{
		const Bone* bone = m_rest_pose->GetBoneByIndex(bone_id);
		Math::quat res = m_animation.at(frame).at(bone->GetName()).m_rotation;
//		if (parent == -1)
			return res;	
	//	return GetRotation(parent, frame)*res;
	}

	const Math::mat4 SkinAnimation::GetMeshOffset() const
	{
		return m_mesh_offset;
	}

	const Math::mat4 SkinAnimation::GetTransform(unsigned int bone_id, unsigned int frame) const
	{
		const Bone* bone = m_rest_pose->GetBoneByIndex(bone_id);
		Math::quat res = m_animation.at(frame).at(bone->GetName()).m_rotation;
	//	if (parent == -1)
			return res.ToMatrix4x4();	
		//return GetTransform(parent, frame)*res.ToMatrix4x4();
	}

/*	const Math::mat4 SkinAnimation::GetInterpolatedTransform(unsigned bone_id, unsigned frame1, unsigned frame2, float t) const
	{
		Math::quat q1 = GetRotation(frame1, bone_id);
		Math::quat q2 = GetRotation(frame2, bone_id);
		Math::vec3 p1 = GetPosition(frame1, bone_id);
		Math::vec3 p2 = GetPosition(frame2, bone_id);

		Math::quat q = Math::cosine_interpolation(q1, q2, t);
		q.Normalize();
		Math::vec3 p = Math::linear_interpolation(p1, p2, t);

		const Bone* b = m_rest_pose->GetBoneByIndex(bone_id);
		Math::mat4 res = q.ToMatrix4x4();
		if (b->GetParent() < 0)
			return res;
		const Bone* pb = m_rest_pose->GetBoneByIndex(b->GetParent()->GetIndex());
		res = GetInterpolatedTransform(b->GetParent()->GetIndex(), frame1, frame2, t)
			* m_mesh_offset.Inversed()*b->GetBoneMatrix()*res*b->GetBoneMatrix().Inversed()*m_mesh_offset;
		return res;
	}*/


	const Math::vec3 SkinAnimation::GetPosition(unsigned int bone_id, unsigned int frame) const
	{
		const Bone* bone = m_rest_pose->GetBoneByIndex(bone_id);
		Math::vec3 res = m_animation.at(frame).at(bone->GetName()).m_position;
//		if (parent == -1)
			return res;	
	//	return GetPosition(parent, frame)+res;
	}

	const Bone& SkinAnimation::GetBone(unsigned id) const
	{
		return *m_rest_pose->GetBoneByIndex(id);
	}

	const System::string SkinAnimation::GetName() const
	{
		return m_name;
	}

	const Armature& SkinAnimation::GetRestPosition() const
	{
		return *m_rest_pose;
	}

	float SkinAnimation::GetDuration() const
	{
		return m_duration;
	}

	float SkinAnimation::GetTicksPerSecond() const
	{
		return m_tick_per_second;
	}

	void SkinAnimation::SetName(const System::string& name)
	{
		m_name = name;
	}

	void SkinAnimation::SetMeshOffset(const Math::mat4& mat)
	{
		m_mesh_offset = mat;
	}

	void SkinAnimation::SetDuration(float duration)
	{
		m_duration = duration;
	}

	void SkinAnimation::SetTicksPerSecond(float tps)
	{
		m_tick_per_second = tps;
	}

	void SkinAnimation::SetRestPosition(Armature* pos)
	{
		m_rest_pose = pos;
	}

	void SkinAnimation::SetAnimationSize(unsigned bones_count, unsigned frames_count)
	{
	}

	void SkinAnimation::SetRotation(const Math::quat& rot, unsigned bone_id, unsigned frame_id)
	{
		m_animation[frame_id][m_rest_pose->GetBoneByIndex(bone_id)->GetName()].m_rotation = rot;
		//m_animation.At(frame_id, bone_id).m_rotation = rot;
	}

	void SkinAnimation::SetPosition(const Math::vec3& pos, unsigned bone_id, unsigned frame_id)
	{
		m_animation[frame_id][m_rest_pose->GetBoneByIndex(bone_id)->GetName()].m_position = pos;
		//m_animation.At(frame_id, bone_id).m_position = pos;
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