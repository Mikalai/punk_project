#ifndef _H_PUNK_VIRTUAL_ARMATURE
#define _H_PUNK_VIRTUAL_ARMATURE

#include <memory>
#include <vector>

#include "../../config.h"
#include "../data/entity.h"
#include "bone.h"
#include "types.h"

#include "../../system/object.h"
#include "../../system/resource_manager.h"
#include "../../string/string.h"

namespace Virtual
{
	class Entity;
	
	class  PUNK_ENGINE Armature : public System::Object
	{
	public:
		Armature();
		Armature(const Armature&);
		Armature& operator = (const Armature&);

		void AddRootBone(Bone* bone);
		Bone* GetBoneByName(const System::string& name);
		const Bone* GetBoneByName(const System::string& name) const;
		Bone* GetBoneByIndex(int index);
		const Bone* GetBoneByIndex(int index) const;		
		int GetRootsBonesCount() const { return m_root_bones.size(); }
		Bone* GetRootBone(int index) { return m_root_bones[index]; }
		int GetBonesCount() const;

		void PrintDebug(Bone* parent, int level = 0);

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Armature();

		static System::Proxy<Armature> CreateFromFile(const System::string& path);
		static System::Proxy<Armature> CreateFromStream(std::istream& stream);

		void UpdateHierarchy();
	private:
		void CacheBones(Bone* b);
		void Clear();

	private:
		std::vector<Bone*> m_root_bones;
		BonesCache m_cache;
		BonesNamedCache m_named_cache;
	};
}

REGISTER_MANAGER(L"resource.armatures", L"*.armature", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE, Virtual, Armature, return, return);

#endif	//	_H_PUNK_VIRTUAL_ARMATURE