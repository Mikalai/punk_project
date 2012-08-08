#ifndef _H_PUNK_SKELETON
#define _H_PUNK_SKELETON

#include "../config.h"
#include "bone.h"
#include <memory>
#include "../animation/armature_animation.h"

namespace System
{
	class string;
}

namespace Utility
{
	typedef std::map<BoneName, std::shared_ptr<Bone>> BonesCollection;
	typedef std::vector<Bone*> BonesCache;

	class Object;

	class LIB_UTILITY Armature2
	{
		int m_bones_count;
		Bone* m_root_bone;		
	public:
		void SetRootBone(Bone* bone);
		Bone* GetRootBone(Bone* bone);
	};
	
	class  LIB_UTILITY Armature
	{
		System::string m_name;
		BonesCollection m_bones;
		BonesCache m_cache;		
		Object* m_armature;
		ArmatureAnimation m_animation;
		//Math::Matrix4x4<float> m_mesh_offset;
	public:
		Armature();
		void AddBone(Bone* parent);/*, Bone* bone);
		void AddBone(const System::string& parent_name, Bone* bone);
		void AddBone(unsigned parent_index, Bone* bone);*/

		void SetName(const System::string& name);
		const System::string& GetName() const;

		Bone* GetBoneByName(const System::string& name);
		const Bone* GetBoneByName(const System::string& name) const;
		Bone* GetBoneByIndex(int index);
		const Bone* GetBoneByIndex(int index) const;
		void CacheBones();

		void SetMeshOffset(const Math::Matrix4x4<float>& offset);
		const Math::Matrix4x4<float>& GetMeshOffset() const;

		int GetBonesCount() const;
		ArmatureAnimation& GetArmatureAnimation();
		const ArmatureAnimation& GetArmatureAnimation() const;

		void PrintDebug(Bone* parent, int level = 0);

		void Save(std::ostream& stream);
		void Load(std::istream& stream);

		void FromFileArmature(const System::string& filename);

		void SetArmatureObject(Object* obj) { m_armature = obj; }
		Object* GetArmatureObject() { return m_armature; }
		const Object* GetArmatureObject() const { return m_armature; }
	};

	typedef Armature* ArmatureRef;
	typedef std::map<System::string, std::shared_ptr<Armature>> ArmatureCollection;
}

#endif