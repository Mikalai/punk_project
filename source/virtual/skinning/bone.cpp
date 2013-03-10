#include <iostream>
#include "bone.h"
#include "armature.h"
#include "../../system/logger.h"
#include "../../system/hresource.h"
#include "../../math/quat.h"
#include "../../math/mat4.h"
#include "../../math/vec3.h"
#include "../../math/helper.h"
#include "../animation/armature_animation_Mixer.h"
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
		m_last_local_matrix_update = bone.m_last_local_matrix_update;
		m_last_global_matrix_update = bone.m_last_global_matrix_update;
		m_last_get_global_matrix = bone.m_last_get_global_matrix;
		m_length = bone.m_length;
		m_need_update_global_matrix = bone.m_need_update_global_matrix;
		m_parent = nullptr;

		for each (auto bone in m_children)
		{
			Bone* bone = new Bone(*bone);			
			AddChild(bone);
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
			m_last_local_matrix_update = bone.m_last_local_matrix_update;
			m_last_global_matrix_update = bone.m_last_global_matrix_update;
			m_last_get_global_matrix = bone.m_last_get_global_matrix;
			m_length = bone.m_length;
			m_need_update_global_matrix = bone.m_need_update_global_matrix;
			m_parent = nullptr;

			for each (auto bone in m_children)
			{
				Bone* bone = new Bone(*bone);			
				AddChild(bone);
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
		if (std::find(m_children.begin(), m_children.end(), child) == m_children.end())
		{
			m_children.push_back(child);
			if (child->GetParent() != this)
				child->SetParent(this);
		}
	}

	Bone* Bone::Find(const System::string& name)
	{
		for each (Bone* bone in m_children)
		{
			if (bone->GetName() == name)
				return bone;
		}

		for each (Bone* bone in m_children)
		{
			Bone* res = bone->Find(name);
			if (res)
				return res;
		}

		return nullptr;
	}

		
	const Math::mat4& Bone::GetAnimatedGlobalMatrix() const
	{
		if (m_need_update_global_matrix)
		{
			if (m_parent)
			{
//				Math::mat4 m;
				//m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
				m_last_global_matrix_update = m_parent->GetAnimatedGlobalMatrix() *  m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
			}
			else
			{
				m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
			}
			m_need_update_global_matrix = false;
		}
		return m_last_global_matrix_update;
	}
	
	const Math::mat4& Bone::GetAnimatedGlobalMatrix2() const
	{
		if (m_need_update_global_matrix2)
		{
			if (m_parent)
			{
//				Math::mat4 m;
				//m_last_global_matrix_update = m_local_matrix * m_bone_matrix * m_local_matrix.Inversed();
				m_last_global_matrix_update2 = m_parent->GetAnimatedGlobalMatrix2() *  m_local_matrix * m_bone_matrix;
			}
			else
			{
				m_last_global_matrix_update2 = m_local_matrix * m_bone_matrix;
			}
			m_need_update_global_matrix2 = false;
		}
		return m_last_global_matrix_update2;
	}
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

	void Bone::UpdatePose(Virtual::AnimationMixer* m, float frame, bool deep)
	{
		if (!m || m->GetType() != System::ObjectType::ARMATURE_ANIMATION_MIXER)
		{		
			out_error() << "Can't update bone position " << m_name << ", because of bad animation Mixer" << std::endl;
			return;
		}

		ArmatureAnimationMixer* Mixer = static_cast<ArmatureAnimationMixer*>(m);

		if (m_last_get_global_matrix != frame)
		{
			m_last_get_global_matrix = frame;
			Mixer->GetBoneMatrix(m_name, m_last_local_matrix_update);			
			m_need_update_global_matrix = true;

			if (deep)
			{
				for (auto bone : m_children)
				{
					bone->UpdatePose(Mixer, frame, deep);
				}
			}
		}		
	}

	void Bone::ResetCache()
	{
		m_need_update_global_matrix = true;
	}

	bool Bone::Save(std::ostream& stream) const
	{		
		m_name.Save(stream);
		m_parent_name.Save(stream);
//		stream.write(reinterpret_cast<const char*>(&m_index_in_armature), sizeof(m_index_in_armature));
		m_global_matrix.Save(stream);
		m_bone_matrix.Save(stream);
		m_last_local_matrix_update.Save(stream);
		m_last_global_matrix_update.Save(stream);
		stream.write(reinterpret_cast<const char*>(&m_last_get_global_matrix), sizeof(m_last_get_global_matrix));
		stream.write(reinterpret_cast<const char*>(&m_need_update_global_matrix), sizeof(m_need_update_global_matrix));		

		int children_count = m_children.size();
		stream.write(reinterpret_cast<const char*>(&children_count), sizeof(children_count));
		for (auto bone : m_children)
		{
			bone->Save(stream);
		}
		return true;
	}

	bool Bone::Load(std::istream& stream)
	{
		Clear();
		m_name.Load(stream);
		m_parent_name.Load(stream);
//		stream.read(reinterpret_cast<char*>(&m_index_in_armature), sizeof(m_index_in_armature));
		m_global_matrix.Load(stream);
		m_bone_matrix.Load(stream);
		m_last_local_matrix_update.Load(stream);
		m_last_global_matrix_update.Load(stream);
		stream.read(reinterpret_cast<char*>(&m_last_get_global_matrix), sizeof(m_last_get_global_matrix));
		stream.read(reinterpret_cast<char*>(&m_need_update_global_matrix), sizeof(m_need_update_global_matrix));		

		int children_count = 0;
		stream.read(reinterpret_cast<char*>(&children_count), sizeof(children_count));
		for (int i = 0; i < children_count; ++i)
		{
			std::unique_ptr<Bone> child(new Bone);
			if (!child->Load(stream))
				return (out_error() << "Can't load children bones" << std::endl, false);
			AddChild(child.release());
		}		
		return true;
	}

	int Bone::GetIndex() const
	{
		return m_index;
	}
	
	void Bone::SetIndex(int index)
	{
		m_index = index;
	}
}