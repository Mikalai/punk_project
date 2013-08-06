#ifndef _H_PUNK_VIRTUAL_ARMATURE
#define _H_PUNK_VIRTUAL_ARMATURE

#include <memory>
#include <vector>

#include "../../config.h"
#include "../data/entity.h"
#include "bone.h"
#include "types.h"

#include "../../system/object.h"
#include "../../system/aop/aop.h"
#include "../../string/string.h"

namespace Virtual
{
	class Entity;
	
    class  PUNK_ENGINE_API Armature : public System::Object
	{
	public:
        typedef std::vector<System::string> Actions;
        typedef std::vector<Bone*> Bones;
    public:
		Armature();
        Armature(const Armature&) = delete;
        Armature& operator = (const Armature&) = delete;
        virtual ~Armature();

		void AddRootBone(Bone* bone);
		int GetBoneIndex(const System::string& name) const;
		Bone* GetBoneByName(const System::string& name);
		const Bone* GetBoneByName(const System::string& name) const;
		Bone* GetBoneByIndex(int index);
		const Bone* GetBoneByIndex(int index) const;		
		int GetRootsBonesCount() const { return m_root_bones.size(); }
		Bone* GetRootBone(int index) { return m_root_bones[index]; }
		int GetBonesCount() const;

        void AddActionName(const System::string& value);
        bool IsActionSupported(const System::string& value);
        const Actions& GetSupportedActionArray() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

        void PrintDebug(Bone* parent, int level = 0);

        virtual void Save(System::Buffer *buffer) const override;
        virtual void Load(System::Buffer *buffer) override;


		virtual void UpdateHierarchy();
	private:
		void CacheBones(Bone* b);
		void Clear();

	private:
        Bones m_root_bones;
		BonesCache m_cache;
		BonesNamedCache m_named_cache;
        Actions m_supported_actions;
        System::string m_name;

        PUNK_OBJECT(Armature)
	};
}

//REGISTER_MANAGER(L"resource.armatures", L"*.armature", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE, Virtual, Armature, return, return);

#endif	//	_H_PUNK_VIRTUAL_ARMATURE
