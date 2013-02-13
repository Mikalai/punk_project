#include "terrain_processor.h"
#include "terrain_cell.h"

namespace Virtual
{

	TerrainProcessor::TerrainProcessor(TerrainCell* cell)
	{
		m_terrain_cell = cell;
		m_data = 0;
		m_size = 0;
	}

	System::StreamingStepResult TerrainProcessor::LockDeviceObject()
	{		
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainProcessor::UnlockDeviceObject()
	{
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainProcessor::Process(void* data, unsigned size)
	{
		m_data = data;
		m_size = size;
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainProcessor::CopyToResource()
	{
		TerrainData* terrain_data(new TerrainData);
		terrain_data->SetData(m_data);
		m_terrain_cell->SetDataCached(terrain_data);
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainProcessor::SetResourceError()
	{
		m_terrain_cell->DropCache();
		delete[] m_data;
		return System::STREAM_OK;
	}

	TerrainProcessor::~TerrainProcessor()
	{
	}
}