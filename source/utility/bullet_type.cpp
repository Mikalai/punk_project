#include <ostream>
#include <istream>
#include <string.h>
#include "bullet_type.h"

namespace Utility
{
	void BulletType::SetName(const wchar_t* name)
	{
		wcsncpy(m_name, name, MAX_NAME_SIZE - 1);
	}

	void BulletType::SetDescription(const wchar_t* desc)
	{
		wcsncpy(m_description, desc, MAX_DESCRIPTION_SIZE - 1);
	}

	void BulletType::Save(std::ostream& stream)
	{
		stream.write(reinterpret_cast<const char*>(this), sizeof(BulletType));
	}

	void BulletType::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(this), sizeof(BulletType));
	}
}