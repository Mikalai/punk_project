#include "storable_data.h"
#include "logger.h"

namespace System
{
	bool StorableData::Save(std::ostream& stream) const
	{
		return m_storage_name.Save(stream);		
	}
	
	bool StorableData::Load(std::istream& stream)
	{
		return m_storage_name.Load(stream);
	}
}