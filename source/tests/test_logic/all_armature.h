#ifndef _H_ALL_ARMATURE
#define _H_ALL_ARMATURE

#include "../punk_engine/utility/model/armature.h"
#include "../punk_engine/system/environment.h"

struct AllArmature
{
	std::auto_ptr<Utility::Armature> m_male_armature;

	static std::auto_ptr<AllArmature> m_instance;

	AllArmature()
	{
		m_male_armature.reset(new Utility::Armature);
		m_male_armature->FromFileArmature(System::Environment::Instance()->GetModelFolder() + L"animated_male.armture");
		m_male_armature->GetArmatureAnimation().EnableTrack(L"walk", false);
		m_male_armature->GetArmatureAnimation().EnableTrack(L"idle", true);
		m_male_armature->GetArmatureAnimation().EnableTrack(L"die", false);
		
	}

	static AllArmature* Instance() 
	{
		if (!m_instance.get())
			m_instance.reset(new AllArmature);
		return m_instance.get();
	}

	static void Destroy()
	{
		m_instance.reset(0);
	}
};


#endif