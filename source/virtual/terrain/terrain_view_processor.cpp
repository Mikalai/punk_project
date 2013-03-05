#include "../../gpu/common/texture2d.h"
#include "../../system/logger.h"
#include "terrain_view_processor.h"
#include "terrain_view.h"

namespace Virtual
{
	TerrainViewProcessor::TerrainViewProcessor(const TerrainViewProcessorDesc& desc)
	{
		m_desc = desc;
		m_data = 0;
		m_size = 0;
	}

	
	System::StreamingStepResult TerrainViewProcessor::LockDeviceObject()
	{
		if (m_desc.m_height_map->GetWidth() != m_desc.m_view_size
			|| m_desc.m_height_map->GetWidth() != m_desc.m_view_size)			
		{
			if (!m_desc.m_height_map->Create(m_desc.m_view_size, m_desc.m_view_size, ImageModule::IMAGE_FORMAT_R32F, 0, true))
				return (out_error() << "Can't lock object" << std::endl, System::STREAM_ERROR);
		}
		m_desc.m_device_ptr = m_desc.m_height_map->Map();
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainViewProcessor::UnlockDeviceObject()
	{		
		m_desc.m_height_map->Unmap(0);
		m_data = 0;
		m_size = 0;
		if (m_desc.OnEnd)
			m_desc.OnEnd(m_desc.m_on_end_data);
		return System::STREAM_OK;
	}
	
	System::StreamingStepResult TerrainViewProcessor::Process(void* data, unsigned size)
	{
		m_data = data;
		m_size = size;
		//	here it will be possible to convert float point representation to any other
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainViewProcessor::CopyToResource()
	{
		memcpy(m_desc.m_device_ptr, m_data, m_size);
		reinterpret_cast<Virtual::TerrainView*>(m_desc.m_on_end_data)->UpdatePhysics();
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainViewProcessor::SetResourceError()
	{
		return System::STREAM_OK;
	}
}
