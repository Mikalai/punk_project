#ifndef _H_PUNK_LOGIC_WEAPON
#define _H_PUNK_LOGIC_WEAPON

#include "config.h"
#include "../utility/weapon_type.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE Weapon
	{
		int m_type_index;
		Math::mat4 m_transform;

	public:

		void SetTypeIndex(int index) { m_type_index = index; }
		int GetTypeIndex() { return m_type_index; }
		
		Utility::WeaponType* GetType() { return 0; }
		const Utility::WeaponType* GetType() const { return 0; }

		Math::mat4& GetTransform() { return m_transform; }
		const Math::mat4& GetTransform() const { return m_transform; }

	};
}

#endif	//_H_PUNK_LOGIC_WEAPON