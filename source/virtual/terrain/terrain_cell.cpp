#include "../../system/errors/module.h"
#include "../../system/logger.h"
#include "terrain_cell.h"

namespace Virtual
{
    void TerrainRawDataSource::Save(System::Buffer *buffer) const
	{
        buffer->WriteString(m_raw_file);
	}

    void TerrainRawDataSource::Load(System::Buffer *buffer)
	{
        m_raw_file = buffer->ReadString();
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

    void TerrainCell::Save(System::Buffer *buffer) const
	{
        m_core.m_location.Save(buffer);
        buffer->WriteReal32(m_core.m_base_height);
        buffer->WriteSigned32(m_core.m_is_valid);
        buffer->WriteString(m_name);
        m_source.Save(buffer);
	}

    void TerrainCell::Load(System::Buffer *buffer)
	{
        m_core.m_location.Load(buffer);
        m_core.m_base_height = buffer->ReadReal32();
        m_core.m_is_valid = buffer->ReadSigned32();
        m_name = buffer->ReadString();
        m_source.Load(buffer);
	}

	TerrainCell::~TerrainCell()
	{
		delete m_data_cache;
		m_data_cache = nullptr;
	}

}
