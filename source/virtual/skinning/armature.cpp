#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include "armature.h"
#include "../../system/buffer.h"
#include "../../utility/descriptors/armature_desc.h"
#include "../../utility/descriptors/bone_desc.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Armature, "Virtual.Armature", PUNK_ARMATURE, SaveArmature, LoadArmature, &System::Object::Info.Type);

	Armature::Armature()
	{
        Info.Add(this);
    }

    Armature::~Armature()
    {
        Clear();
        Info.Remove(this);
    }

    void Armature::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& Armature::GetName() const
    {
        return m_name;
    }

	Bone* Armature::GetBoneByName(const System::string& name)
	{
		auto it = m_named_cache.find(name);
		if (it == m_named_cache.end())
		{
			//	try to find in root bones
			for (Bone* bone : m_root_bones)
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
		for (auto bone : m_root_bones)
		{
            //bone->UpdatePose(0, 0, true);
			CacheBones(bone);
		}
	}

	void Armature::CacheBones(Bone* b)
	{
//		b->SetIndexInArmature(m_cache.size());
		size_t index = m_cache.size();
		b->SetIndex((int)index);
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


    void Armature::Clear()
	{
		for (auto bone : m_root_bones)
			delete bone;
		m_root_bones.clear();
		m_cache.clear();
		m_named_cache.clear();
    }

	int Armature::GetBoneIndex(const System::string& value) const
	{
		for (int i = 0, max_i = m_cache.size(); i != max_i; ++i)
		{
			if (m_cache[i]->GetName() == value)
				return i;
		}
		throw System::PunkInvalidArgumentException(L"There is no bone with name " + value);
	}

    void Armature::AddActionName(const System::string& value)
    {
        auto it = std::find(m_supported_actions.begin(), m_supported_actions.end(), value);
        if (it != m_supported_actions.end())
            return;
        m_supported_actions.push_back(value);
    }

    bool Armature::IsActionSupported(const System::string& value)
    {
        auto it = std::find(m_supported_actions.begin(), m_supported_actions.end(), value);
        return it != m_supported_actions.end();
    }

    const Armature::Actions& Armature::GetSupportedActionArray() const
    {
        return m_supported_actions;
    }

    void SaveArmature(System::Buffer *buffer, const System::Object* o)
    {
        System::SaveObject(buffer, 0);
        const Armature* a = Cast<const Armature*>(o);
        unsigned count = (unsigned)a->m_root_bones.size();
        buffer->WriteUnsigned32(count);
        for (auto root : a->m_cache)
        {
            SaveBone(buffer, *root);
        }
    }

    void LoadArmature(System::Buffer *buffer, System::Object* o)
    {
        System::LoadObject(buffer, o);
        Armature* a = Cast<Armature*>(o);
        a->Clear();
        unsigned count = buffer->ReadUnsigned32();
        for (unsigned i = 0; i != count; ++i)
        {
            std::unique_ptr<Bone> bone(new Bone);
            LoadBone(buffer, *bone);
            a->CacheBones(bone.get());
            a->m_root_bones.push_back(bone.release());
        }
    }
}
