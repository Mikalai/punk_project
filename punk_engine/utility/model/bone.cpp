#include <iostream>
#include "bone.h"
#include "armature.h"
#include "../../math/quat.h"
#include "../../math/mat4.h"
#include "../../math/vec3.h"

namespace Utility
{
	const Math::mat4& Bone::GetWorldMatrix() const
	{
		return m_global_matrix;
	}

	const Math::mat4& Bone::GetBoneMatrix() const
	{
		return m_bone_matrix;
	}

	const System::string& Bone::GetName() const
	{
		return m_name;
	}

	const Bone* Bone::GetParent() const
	{
		return m_parent;
	}

	void Bone::SetMatrix(const Math::mat4& matrix)
	{
		m_global_matrix = matrix;
	}

	void Bone::SetName(const System::string& name)
	{
		m_name = name;
	}

	void Bone::SetParent(Bone* parent)
	{
		m_parent = parent;
		if (m_parent != 0)
			m_parent->AddChild(this);
	}

	void Bone::AddChild(Bone* child)
	{
		if (std::find(m_children.begin(), m_children.end(), child) == m_children.end())
		{
			m_children.push_back(child);
			if (child->GetParent() != this)
				child->SetParent(this);
		}
	}

	void Bone::SetBoneMatrix(const Math::mat4& m)
	{
		m_bone_matrix = m;
	}

	Math::mat4& Bone::GetAnimatedGlobalMatrix()
	{
		if (m_need_update_global_matrix)
		{
			Math::mat4 m = m_last_local_matrix_update/**/;
			/*if (m_index_in_armature == -1)
				m = Math::mat4::CreateRotation(1, 0, 0, 3.14 / 2.0);
			else
				m = Math::mat4::CreateIdentity();/**/

			if (m_parent)
			{
				m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() /** m_armature->GetMeshOffset().Inversed()*/ * m_global_matrix * m * m_global_matrix.Inversed() /** m_armature->GetMeshOffset()/**/;
				/*m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() * m_armature->GetMeshOffset().Inversed() * m_global_matrix * m * m_global_matrix.Inversed() * m_armature->GetMeshOffset();*/
				Math::vec3 t = m_last_global_matrix_update.TranslationPart();
				Math::quat q = m_last_global_matrix_update.ToQuaternion();
				Math::vec4 angle_axis = q.ToAngleAxis();
				angle_axis = angle_axis;
			}
			else
			{
				m_last_global_matrix_update = /*m_armature->GetMeshOffset() **/ m_global_matrix * m * m_global_matrix.Inversed() /***m_armature->GetMeshOffset().Inversed()/**/;		/**/
				/*m_last_global_matrix_update = m_armature->GetMeshOffset().Inversed() * m_global_matrix * m * m_global_matrix.Inversed() *m_armature->GetMeshOffset();		*/
			}
			m_need_update_global_matrix = false;
		}
		return m_last_global_matrix_update;
	}

	void Bone::UpdatePose(int frame)
	{
		if (frame == 20 && m_index_in_armature == 10)
			frame = 20;
		if (m_last_get_global_matrix != frame)
		{
			m_last_get_global_matrix = frame;
			Math::vec3 pos = m_animation.GetPosition(frame);
			Math::quat rot = m_animation.GetRotation(frame).Normalized();
			m_last_local_matrix_update = Math::mat4::CreateTranslate(pos) * rot.ToMatrix4x4();
			m_need_update_global_matrix = true;
		}		
	}

	AnimationMixer& Bone::GetAnimationMixer()
	{
		return m_animation;
	}

	const AnimationMixer& Bone::GetAnimationMixer() const
	{
		return m_animation;
	}

	int Bone::GetIndex() const
	{
		return m_index_in_armature;
	}

	void Bone::SetIndexInArmature(int value)
	{
		m_index_in_armature = value;
	}

	void Bone::SetArmature(Armature* armature)
	{
		m_armature = armature;
	}

	Armature* Bone::GetArmature() 
	{
		return m_armature;
	}

	void Bone::ResetCache()
	{
		m_need_update_global_matrix = true;
	}
}