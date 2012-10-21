#include <algorithm>
#include <iostream>
#include <fstream>
#include "armature.h"
#include "../../utility/descriptors/armature_desc.h"
#include "../../utility/descriptors/bone_desc.h"

#include "../../system/logger.h"

namespace Virtual
{
	Armature::Armature() {}

	Armature::Armature(const Utility::ArmatureDesc& desc)
	{
		m_name = desc.m_name;
		if (!BuildSkeleton(desc.m_bones))
		{
			out_error() << "Can't build armature from provided descriptor" << std::endl;
			return;
		}
	}

	bool Armature::BuildSkeleton(const std::vector<Utility::BoneDesc*>& bones)
	{
		bool result = false;
		m_cache.clear();
		m_named_cache.clear();

		for (auto root_it : bones)
		{
			if (root_it->m_parent == L"")
			{

				std::auto_ptr<Bone> root(new Bone(*root_it));
				root->SetParent(nullptr);
				root->SetArmature(this);
				root->SetIndexInArmature(0);

				//	insert first cache record
				m_cache.push_back(root.get());
				m_named_cache[root->GetName()] = root.get();

				if (!BuildBone(root.get(), bones))
				{
					out_error() << "Error occured while building bone hierarchy" << std::endl;
					return false;
				}

				m_root_bones.push_back(root.get());
				root.release();				
				result = true;
			}
		}
		return result;
	}

	bool Armature::BuildBone(Bone* parent, const std::vector<Utility::BoneDesc*>& bones)
	{
		for (auto desc : bones)
		{
			if (desc->m_parent == parent->GetName())
			{

				std::unique_ptr<Bone> bone(new Bone(*desc));
				bone->SetParent(parent);
				bone->SetArmature(this);
				bone->SetIndexInArmature(m_cache.size());
				m_cache.push_back(bone.get());;
				m_named_cache[bone->GetName()] = bone.get();
				parent->AddChild(bone.get());

				if (!BuildBone(bone.get(), bones))
					return false;			

				bone.release();
			}
		}
		return true;
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
		return m_named_cache.at(name);
	}

	const Bone* Armature::GetBoneByName(const System::string& name) const
	{
		return m_named_cache.at(name);
	}

	Bone* Armature::GetBoneByIndex(int index)
	{
		return m_cache[index];
	}

	const Bone* Armature::GetBoneByIndex(int index) const
	{
		return m_cache[index];
	}

	void Armature::CacheBones(Bone* b)
	{
		b->SetIndexInArmature(m_cache.size());
		m_cache.push_back(b);
		m_named_cache[b->GetName()] = b;

		for (auto bone : b->GetChildren())
		{
			CacheBones(bone);
		}
	}

	int Armature::GetBonesCount() const
	{
		return m_cache.size();
	}

	void Armature::PrintDebug(Bone* parent, int level)
	{

	}

	bool Armature::Save(std::ostream& stream)
	{
		m_name.Save(stream);
		int count = m_root_bones.size();
		stream.write((char*)&count, sizeof(count));
		for (auto root : m_cache)
		{
			root->Save(stream);		
		}
		return true;
	}

	bool Armature::Load(std::istream& stream)
	{
		m_name.Load(stream);
		int count = 0;
		stream.read((char*)&count, sizeof(count));
		for (int i = 0; i < count; ++i)
		{
			std::unique_ptr<Bone> bone(new Bone);
			bone->Load(stream);
			CacheBones(bone.get());
			m_root_bones.push_back(bone.release());			
		}
		return true;
	}

	Armature::~Armature()
	{
		for (auto bone : m_root_bones)
			delete bone;
	}

	Armature* Armature::CreateFromFile(const System::string& path)
	{
		std::unique_ptr<Armature> result(new Armature);
		std::ifstream stream(path.Data(), std::ios_base::binary);
		if (!result->Load(stream))
			return (out_error() << "Can't create armature from file " << path << std::endl, nullptr);
		return result.release();
	}

	Armature* Armature::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<Armature> result(new Armature);
		if (!result->Load(stream))
			return (out_error() << "Can't create armature from stream" << std::endl, nullptr);
		return result.release();
	}
}