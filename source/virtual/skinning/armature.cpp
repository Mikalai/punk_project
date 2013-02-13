#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include "armature.h"
#include "../../utility/descriptors/armature_desc.h"
#include "../../utility/descriptors/bone_desc.h"

namespace Virtual
{
	Armature::Armature()
	{
		SetType(System::ObjectType::ARMATURE);
	}

	Armature::Armature(const Armature& armature)
	{
		for each (auto bone in armature.m_root_bones)
		{
			Bone* root_bone = new Bone(*bone);
			m_root_bones.push_back(root_bone);
			CacheBones(root_bone);
		}
	}

	Armature& Armature::operator = (const Armature& armature)
	{
		if (this != &armature)
		{
			Clear();
			for each(Bone* bone in armature.m_root_bones)
			{
				Bone* root_bone = new Bone(*bone);
				m_root_bones.push_back(root_bone);
				CacheBones(root_bone);
			}
		}
		return *this;
	}

	Bone* Armature::GetBoneByName(const System::string& name)
	{
		auto it = m_named_cache.find(name);
		if (it == m_named_cache.end())
		{
			//	try to find in root bones
			for each (Bone* bone in m_root_bones)
			{
				if (bone->GetName() == name)
					return bone;
				Bone* res = bone->Find(name);
				if (res)
					return res;
			}
			return nullptr;
		}
		return it->second;
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

	void Armature::UpdateHierarchy()
	{
		m_cache.clear();
		m_named_cache.clear();
		for each (auto bone in m_root_bones)
		{
			bone->UpdatePose(0, 0, true);
			CacheBones(bone);
		}
	}

	void Armature::CacheBones(Bone* b)
	{
//		b->SetIndexInArmature(m_cache.size());
		m_cache.push_back(b);
		m_named_cache[b->GetName()] = b;

		for (auto bone : b->GetChildren())
		{
			CacheBones(bone);
		}
	}

	void Armature::AddRootBone(Bone* b)
	{
		m_root_bones.push_back(b);
		CacheBones(b);
	}

	int Armature::GetBonesCount() const
	{
		return m_cache.size();
	}

	void Armature::PrintDebug(Bone* parent, int level)
	{

	}

	bool Armature::Save(std::ostream& stream) const
	{
		System::Object::Save(stream);

		int count = (int)m_root_bones.size();
		stream.write((char*)&count, sizeof(count));
		for (auto root : m_cache)
		{
			root->Save(stream);		
		}
		return true;
	}

	bool Armature::Load(std::istream& stream)
	{
		Clear();

		System::Object::Load(stream);

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

	void Armature::Clear()
	{
		for (auto bone : m_root_bones)
			delete bone;
		m_root_bones.clear();
		m_cache.clear();
		m_named_cache.clear();
	}

	Armature::~Armature()
	{
		Clear();
	}

	Armature* Armature::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	Armature* Armature::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<Armature> node(new Armature);
		node->Load(stream);
		return node.release();
	}
}

	//bool Armature::BuildSkeleton(const std::vector<Utility::BoneDesc*>& bones)
	//{
	//	bool result = false;
	//	m_cache.clear();
	//	m_named_cache.clear();

	//	for (auto root_it : bones)
	//	{
	//		if (root_it->m_parent == L"")
	//		{

	//			std::auto_ptr<Bone> root(new Bone(*root_it));
	//			root->SetParent(nullptr);
	//			root->SetArmature(this);
	//			root->SetIndexInArmature(0);

	//			//	insert first cache record
	//			m_cache.push_back(root.get());
	//			m_named_cache[root->GetName()] = root.get();

	//			if (!BuildBone(root.get(), bones))
	//			{
	//				out_error() << "Error occured while building bone hierarchy" << std::endl;
	//				return false;
	//			}

	//			m_root_bones.push_back(root.get());
	//			root.release();				
	//			result = true;
	//		}
	//	}
	//	return result;
	//}

	//bool Armature::BuildBone(Bone* parent, const std::vector<Utility::BoneDesc*>& bones)
	//{
	//	for (auto desc : bones)
	//	{
	//		if (desc->m_parent == parent->GetName())
	//		{

	//			std::unique_ptr<Bone> bone(new Bone(*desc));
	//			bone->SetParent(parent);
	//			bone->SetArmature(this);
	//			bone->SetIndexInArmature(m_cache.size());
	//			m_cache.push_back(bone.get());;
	//			m_named_cache[bone->GetName()] = bone.get();
	//			parent->AddChild(bone.get());

	//			if (!BuildBone(bone.get(), bones))
	//				return false;			

	//			bone.release();
	//		}
	//	}
	//	return true;
	//}
