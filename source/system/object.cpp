#include <ostream>
#include <istream>
#include "logger.h"
#include "object.h"

namespace System
{
	bool Object::Save(std::ostream& stream)
	{
		if (!m_storage_name.Save(stream))
			return (out_error() << "Can't save object storage name" << std::endl, false);
		stream.write((char*)&m_type, sizeof(m_type));
		return true;
	}

	bool Object::Load(std::istream& stream)
	{
		if (!m_storage_name.Load(stream))
			return (out_error() << "Can't load object storage name" << std::endl, false);
		stream.read((char*)&m_type, sizeof(m_type));
		return true;
	}
}
