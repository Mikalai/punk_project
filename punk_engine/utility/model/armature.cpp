#include <iostream>
#include "armature.h"

namespace Utility
{
	Armature::Armature() : m_animation(*this) {}

	void Armature::AddBone(Bone* bone)
	{
		bone->SetArmature(this);
		m_bones[bone->GetName()].reset(bone);		
		CacheBones();
	}

	void Armature::SetName(const System::string& name)
	{
		m_name = name;
	}

	const System::string& Armature::GetName() const
	{
		return m_name;
	}

	Bone* Armature::GetBoneByName(const System::string& name)
	{
		return m_bones.at(name).get();
	}

	const Bone* Armature::GetBoneByName(const System::string& name) const
	{
		return m_bones.at(name).get();
	}

	Bone* Armature::GetBoneByIndex(int index)
	{
		return m_cache[index];
	}

	const Bone* Armature::GetBoneByIndex(int index) const
	{
		return m_cache[index];
	}

	void Armature::CacheBones()
	{
		m_cache.clear();		
		int index = 0;
		for (auto it = m_bones.begin(); it != m_bones.end(); ++it)
		{
			m_cache.push_back(it->second.get());
			it->second->SetIndexInArmature(index);
			++index;
		}
	}

	int Armature::GetBonesCount() const
	{
		return m_cache.size();
	}

	ArmatureAnimation& Armature::GetArmatureAnimation()
	{
		return m_animation;
	}

	const ArmatureAnimation& Armature::GetArmatureAnimation() const
	{
		return m_animation;
	}

	void Armature::SetMeshOffset(const Math::Matrix4x4<float>& offset)
	{
		m_mesh_offset = offset;
	}

	const Math::Matrix4x4<float>& Armature::GetMeshOffset() const
	{
		return m_mesh_offset;
	}

	void Armature::PrintDebug(Bone* parent, int level)
	{
		for (auto it = m_bones.begin(); it != m_bones.end(); ++it)
		{
			if (it->second->GetParent() == parent)
			{
				for (int i = 0; i < level; ++i)
					putchar('\t');
				std::wcout << it->second->GetIndex() << L": " << it->second->GetName().Data() << std::endl;
				PrintDebug(it->second.get(), level+1);
			}
		}
	}
}