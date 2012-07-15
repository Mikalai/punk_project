#include <ostream>
#include <istream>
#include <string.h>
#include "weapon_type.h"

namespace Utility
{
	void WeaponType::SetName(const wchar_t* name)
	{
		wcsncpy(m_name, name, MAX_NAME_SIZE - 1);
	}

	void WeaponType::SetDescription(const wchar_t* desc)
	{
		wcsncpy(m_description, desc, MAX_DESCRIPTION_SIZE - 1);
	}

	void WeaponType::Save(std::ostream& stream)
	{
		stream.write(reinterpret_cast<const char*>(this), sizeof(WeaponType));
	}

	void WeaponType::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(this), sizeof(WeaponType));
	}
}