#include <ostream>
#include <istream>
#include "logger.h"
#include "object.h"

namespace System
{
	bool Object::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_modified, sizeof(m_modified));
		stream.write((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Save(stream))
			return (out_error() << "Can't save object storage name" << std::endl, false);
		if (!m_name.Save(stream))
			return (out_error() << "Can't save object name" << std::endl, false);
		if (!m_text.Save(stream))
			return (out_error() << "Can't save object text" << std::endl, false);
		return true;
	}

	bool Object::Load(std::istream& stream)
	{
		stream.read((char*)&m_modified, sizeof(m_modified));
		stream.read((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Load(stream))
			return (out_error() << "Can't load object storage name" << std::endl, false);
		if (!m_name.Load(stream))
			return (out_error() << "Can't save object name" << std::endl, false);
		if (!m_text.Load(stream))
			return (out_error() << "Can't save object text" << std::endl, false);		
		return true;
	}
}
