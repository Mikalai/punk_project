#include "../../system/logger.h"
#include "terrain_cell.h"

namespace Virtual
{
	bool TerrainRawDataSource::Save(std::ostream& stream) const
	{
		if (!m_raw_file.Save(stream))
			return (out_error() << "Can't save terrain raw data source" << std::endl, false);
		return true;
	}

	bool TerrainRawDataSource::Load(std::istream& stream)
	{
		if (!m_raw_file.Load(stream))
			return (out_error() << "Can't load terrain raw data source" << std::endl, false);
		return true;
	}

	TerrainCell::Core::Core()
		: m_location(0,0)
		, m_base_height(0)
		, m_is_valid(false)
	{}
	
	TerrainCell::TerrainCell()
		: m_name(L"cell_0_0")	
		, m_loading(false)
		, m_data_cache(nullptr)
	{}

	bool TerrainCell::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_core, sizeof(m_core));
		if (!m_name.Save(stream))
			return (out_error() << "Can't save cell name" << std::endl, false);

		if (!m_source.Save(stream))
			return (out_error() << "Can't save cell raw file name" << std::endl, false);
		return true;
	}

	bool TerrainCell::Load(std::istream& stream) 
	{
		stream.read((char*)&m_core, sizeof(m_core));
		if (!m_name.Load(stream))
			return (out_error() << "Can't load cell name" << std::endl, false);

		if (!m_source.Load(stream))
			return (out_error() << "Can't load cell raw file name" << std::endl, false);
		return true;
	}

	TerrainCell::~TerrainCell()
	{
		delete m_data_cache;
		m_data_cache = nullptr;
	}

}