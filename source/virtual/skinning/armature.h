#ifndef _H_PUNK_VIRTUAL_ARMATURE
#define _H_PUNK_VIRTUAL_ARMATURE

#include <memory>
#include <vector>

#include "../../config.h"
#include "../data/entity.h"
#include "bone.h"
#include "types.h"

#include "../../system/object.h"
#include "../../string/string.h"

namespace Utility
{
	class ArmatureDesc;
	class BoneDesc;
}

namespace Virtual
{
	class Entity;
	
	class  PUNK_ENGINE Armature : public System::Object
	{
	public:
		Armature();
		Armature(const Utility::ArmatureDesc& desc);

		void SetName(const System::string& name);
		const System::string& GetName() const;

		Bone* GetBoneByName(const System::string& name);
		const Bone* GetBoneByName(const System::string& name) const;
		Bone* GetBoneByIndex(int index);
		const Bone* GetBoneByIndex(int index) const;		

		int GetBonesCount() const;

		void PrintDebug(Bone* parent, int level = 0);

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Armature();

		static Armature* CreateFromFile(const System::string& path);
		static Armature* CreateFromStream(std::istream& stream);

	private:
		Armature(const Armature&);
		Armature& operator = (const Armature&);

	private:
		void CacheBones(Bone* b);
		bool BuildSkeleton(const std::vector<Utility::BoneDesc*>& bones);
		bool BuildBone(Bone* bone, const std::vector<Utility::BoneDesc*>& bones);
		System::string m_name;
		std::vector<Bone*> m_root_bones;
		BonesCache m_cache;
		BonesNamedCache m_named_cache;
	};
}

#endif	//	_H_PUNK_VIRTUAL_ARMATURE