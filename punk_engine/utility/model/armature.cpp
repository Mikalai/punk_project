#include <iostream>
#include <fstream>
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
		//m_mesh_offset = offset;
	}

	const Math::Matrix4x4<float>& Armature::GetMeshOffset() const
	{
		return Math::Matrix4x4<float>();
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

	void Armature::Save(std::ostream& stream)
	{
		m_name.Save(stream);
		int bones_count = m_bones.size();
		stream.write(reinterpret_cast<const char*>(&bones_count), sizeof(bones_count));
		for each (Bone* bone in m_cache)
		{
			bone->Save(stream);
		}
		m_animation.Save(stream);
	}

	void Armature::Load(std::istream& stream)
	{
		m_name.Load(stream);
		int bones_count = 0;
		stream.read(reinterpret_cast<char*>(&bones_count), sizeof(bones_count));
		m_cache.resize(bones_count);
		//
		//	allocate memory for bones
		//
		for (int i = 0; i < bones_count; ++i)
		{
			std::auto_ptr<Bone> bone(new Bone);			
			m_cache[i] = bone.release();
			m_cache[i]->SetArmature(this);			
		}
		//
		//	read data
		//
		for (int i = 0; i < bones_count; ++i)
		{
			m_cache[i]->Load(stream);			
			m_bones[m_cache[i]->GetName()].reset(m_cache[i]);			
		}
		m_animation.Load(stream);
	}

	void Armature::FromFileArmature(const System::string& filename)
	{
		char ansi_filename[2048];
		filename.ToANSI(ansi_filename, 2048);
		std::ifstream file(ansi_filename, std::ios_base::binary);
		if (!file.is_open())
		{
			std::cout << "File " << ansi_filename << " was not opened in "__FUNCSIG__ << std::endl;
			return;
		}
		Load(file);
		file.close();

	}
}