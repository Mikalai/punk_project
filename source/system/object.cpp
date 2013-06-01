#include <ostream>
#include <istream>
#include "object.h"

namespace System
{
	bool Object::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_modified, sizeof(m_modified));
		stream.write((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object storage name");
		if (!m_name.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object name");
		if (!m_text.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object text");
		return true;
	}

	bool Object::Load(std::istream& stream)
	{
		stream.read((char*)&m_modified, sizeof(m_modified));
		stream.read((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Load(stream))
			throw PunkInvalidArgumentException(L"Can't load object storage name");
		if (!m_name.Load(stream))
			throw PunkInvalidArgumentException(L"Can't save object name");
		if (!m_text.Load(stream))
			throw PunkInvalidArgumentException(L"Can't save object text");
		return true;
	}
}
