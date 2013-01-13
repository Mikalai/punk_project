#include "../../system/logger.h"
#include "terrain_cell.h"

namespace Virtual
{
	TerrainCell::Core::Core()
		: m_location(0,0)
		, m_base_height(0)
		, m_is_valid(false)
	{}
	
	TerrainCell::TerrainCell()
		: m_name(L"cell_0_0")
	{}

	bool TerrainCell::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_core, sizeof(m_core));
		if (!m_name.Save(stream))
			return (out_error() << "Can't save cell name" << std::endl, false);

		if (!m_filename.Save(stream))
			return (out_error() << "Can't save cell raw file name" << std::endl, false);
		return true;
	}

	bool TerrainCell::Load(std::istream& stream) 
	{
		stream.read((char*)&m_core, sizeof(m_core));
		if (!m_name.Load(stream))
			return (out_error() << "Can't load cell name" << std::endl, false);

		if (!m_filename.Load(stream))
			return (out_error() << "Can't load cell raw file name" << std::endl, false);
		return true;
	}
}