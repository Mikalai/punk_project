#include <iostream>
#include <algorithm>
#include "bone.h"
#include "armature.h"
#include "../../system/logger.h"
#include "../../system/buffer.h"
#include "../../math/quat.h"
#include "../../math/mat4.h"
#include "../../math/vec3.h"
#include "../../math/helper.h"
#include "../animation/armature_animation_mixer.h"
#include "../../utility/descriptors/bone_desc.h"

namespace Virtual
{
	Bone::Bone()
	{
		m_parent = nullptr;
	}

	Bone::Bone(const Bone& bone)
	{
		m_name = bone.m_name;
		m_global_matrix = bone.m_global_matrix;
		m_bone_matrix = bone.m_bone_matrix;
		m_local_matrix = bone.m_local_matrix;
//		m_last_local_matrix_update = bone.m_last_local_matrix_update;
//		m_last_global_matrix_update = bone.m_last_global_matrix_update;
//		m_last_get_global_matrix = bone.m_last_get_global_matrix;
		m_length = bone.m_length;
//		m_need_update_global_matrix = bone.m_need_update_global_matrix;
		m_parent = nullptr;

		for (auto bone : m_children)
		{
			Bone* b = new Bone(*bone);
			AddChild(b);
		}
	}

	Bone& Bone::operator = (const Bone& bone)
	{
		if (this != &bone)
		{
			Clear();

			m_name = bone.m_name;
			m_global_matrix = bone.m_global_matrix;
			m_bone_matrix = bone.m_bone_matrix;
			m_local_matrix = bone.m_local_matrix;
    //		m_last_local_matrix_update = bone.m_last_local_matrix_update;
        //	m_last_global_matrix_update = bone.m_last_global_matrix_update;
            //m_last_get_global_matrix = bone.m_last_get_global_matrix;
			m_length = bone.m_length;
    //		m_need_update_global_matrix = bone.m_need_update_global_matrix;
			m_parent = nullptr;

			for (auto bone : m_children)
			{
				Bone* b = new Bone(*bone);
				AddChild(b);
			}
		}
		return *this;
	}

	Bone::~Bone()
	{
		Clear();
	}

	void Bone::Clear()
	{
		for (auto bone : m_children)
			delete bone;
		m_children.clear();
	}

	const Math::mat4 Bone::GetWorldMatrix() const
	{
		return m_global_matrix;
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
	}

	void Bone::AddChild(Bone* child)
	{
	    auto it = std::find(m_children.begin(), m_children.end(), child);
		if (it == m_children.end())
		{
			m_children.push_back(child);
			if (child->GetParent() != this)
				child->SetParent(this);
		}
	}

	Bone* Bone::Find(const System::string& name)
	{
		for (Bone* bone : m_children)
		{
			if (bone->GetName() == name)
				return bone;
		}

		for (Bone* bone : m_children)
		{
			Bone* res = bone->Find(name);
			if (res)
				return res;
		}

		return nullptr;
	}


//	const Math::mat4& Bone::GetAnimatedGlobalMatrix() const
//	{
//		if (m_need_update_global_matrix)
//		{
//			if (m_parent)
//			{
////				Math::mat4 m;
//				//m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
//				m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() *  m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
//			}
//			else
//			{
//				m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
//			}
//			m_need_update_global_matrix = false;
//		}
//		return m_last_global_matrix_update;
//	}

//	const Math::mat4& Bone::GetAnimatedGlobalMatrix2() const
//	{
//		if (m_need_update_global_matrix2)
//		{
//			if (m_parent)
//			{
////				Math::mat4 m;
//				//m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
//				m_last_global_matrix_update2 = m_parent->GetAnimatedGlobalMatrix2() *  m_local_matrix * m_bone_matrix;
//			}
//			else
//			{
//				m_last_global_matrix_update2 = m_local_matrix * m_bone_matrix;
//			}
//			m_need_update_global_matrix2 = false;
//		}
//		return m_last_global_matrix_update2;
//	}
	//const Math::mat4& Bone::GetAnimatedGlobalMatrix() const
	//{
	//	if (m_need_update_global_matrix)
	//	{
	//		Math::mat4 m = m_last_local_matrix_update/**/;
	//		/*if (m_index_in_armature == -1)
	//		m = Math::mat4::CreateRotation(1, 0, 0, 3.14 / 2.0);
	//		else
	//		m = Math::mat4::CreateIdentity();/**/

	//		if (m_parent)
	//		{
	//			//m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix(mesh_transform) * mesh_transform.Inversed() * m_global_matrix * m * m_bone_matrix * m_global_matrix.Inversed() * mesh_transform;
	//			m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() * m_bone_matrix;//m_global_matrix * m * m_bone_matrix * m_global_matrix.Inversed() ;
	//			/*m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() * m_armature->GetMeshOffset().Inversed() * m_global_matrix * m * m_global_matrix.Inversed() * m_armature->GetMeshOffset();*/
	//			const Math::vec3 t = m_last_global_matrix_update.TranslationPart();
	//			const Math::quat q = Math::Matrix4x4ToQuaternion(m_last_global_matrix_update);
	//			Math::vec4 angle_axis = q.ToAngleAxis();
	//			angle_axis = angle_axis;
	//		}
	//		else
	//		{
	//			m_last_global_matrix_update = m_bone_matrix;//mesh_transform.Inversed() * m_bone_matrix//* m_global_matrix * m * m_bone_matrix * m_global_matrix.Inversed() * mesh_transform;
	//			/*m_last_global_matrix_update = m_armature->GetMeshOffset().Inversed() * m_global_matrix * m * m_global_matrix.Inversed() *m_armature->GetMeshOffset();		*/
	//		}
	//		m_need_update_global_matrix = false;
	//	}
	//	return m_last_global_matrix_update;
	//}

//	void Bone::UpdatePose(Virtual::AnimationMixer* m, float frame, bool deep)
//	{
//		if (!m || m->GetType() != System::ObjectType::ARMATURE_ANIMATION_MIXER)
//		{
//			out_error() << "Can't update bone position " << m_name << ", because of bad animation Mixer" << std::endl;
//			return;
//		}

//		ArmatureAnimationMixer* Mixer = static_cast<ArmatureAnimationMixer*>(m);

//		if (m_last_get_global_matrix != frame)
//		{
//			m_last_get_global_matrix = frame;
//			Mixer->GetBoneMatrix(m_name, m_last_local_matrix_update);
//			m_need_update_global_matrix = true;

//			if (deep)
//			{
//				for (auto bone : m_children)
//				{
//					bone->UpdatePose(Mixer, frame, deep);
//				}
//			}
//		}
//	}

//	void Bone::ResetCache()
//	{
//		m_need_update_global_matrix = true;
//	}

    int Bone::GetIndex() const
	{
		return m_index;
	}

	void Bone::SetIndex(int index)
	{
		m_index = index;
	}

    void Bone::SetLocalMatrix(const Math::mat4& matrix)
    {
        m_local_matrix = matrix;// m_need_update_global_matrix = true;
    }

    void Bone::SetBoneMatrix(const Math::mat4& matrix)
    {
        m_bone_matrix = matrix;// m_need_update_global_matrix = true;
    }

    const Math::mat4& Bone::GetBoneMatrix() const
    {
        return m_bone_matrix;
    }

    const Math::mat4& Bone::GetLocalMatrix() const
    {
        return m_local_matrix;
    }    

    void SaveBone(System::Buffer* buffer, const Bone& b)
    {
        System::SaveString(buffer, b.m_name);
        System::SaveString(buffer, b.m_parent_name);
        Math::SaveMatrix4f(buffer, b.m_global_matrix);
        Math::SaveMatrix4f(buffer, b.m_bone_matrix);

        unsigned children_count = b.m_children.size();
        buffer->WriteUnsigned32(children_count);
        for (auto bone : b.m_children)
        {
            SaveBone(buffer, *bone);
        }
    }

    void LoadBone(System::Buffer* buffer, Bone& bone)
    {
        bone.Clear();
        System::LoadString(buffer, bone.m_name);
        System::LoadString(buffer, bone.m_parent_name);
        Math::LoadMatrix4f(buffer, bone.m_global_matrix);
        Math::LoadMatrix4f(buffer, bone.m_bone_matrix);

        unsigned children_count = buffer->ReadUnsigned32();
        for (unsigned i = 0; i != children_count; ++i)
        {
            std::unique_ptr<Bone> child(new Bone);
            LoadBone(buffer, *child);
            bone.AddChild(child.release());
        }
    }
}
