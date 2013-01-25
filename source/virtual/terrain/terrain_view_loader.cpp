#include "../../opengl/textures/texture2d.h"
#include "terrain_manager.h"
#include "terrain_view_loader.h"
#include "terrain_loader.h"
#include "terrain_processor.h"

namespace Virtual
{
	TerrainViewLoader::TerrainViewLoader(const TerrainViewLoaderDesc& desc)
	{
		m_desc = desc;
	}

	TerrainViewLoader::~TerrainViewLoader()
	{}

	System::StreamingStepResult TerrainViewLoader::Load()
	{
		System::Proxy<Terrain> terrain = TerrainManager::Instance()->GetTerrain();
		if (!terrain.IsValid())
			return (out_error() << "Manager do not manage any terrain" << std::endl, System::STREAM_ERROR);

		//	find coordinates of the observer position in the map coordinate system
		auto mark = (m_desc.m_view_point - m_desc.m_world_origin) / m_desc.m_block_scale;

		//	find coordinates of the cell
		Math::ivec2 cell;
		auto temp = mark / (float)m_desc.m_view_size;
		cell.Set((int)floor(temp.X()), (int)floor(temp.Y()));

		//	find observer coordinates in the cell coordinate system
		Math::vec2 mark_rel = mark - Math::vec2(cell.X(), cell.Y()) * (float)m_desc.m_block_size;

		//	find size of the view in the map coordinate system
		int mark_size = (int)(m_desc.m_view_size / (float)m_desc.m_block_scale);

		int east_count = ceil(abs((mark_size / 2.0f - (float)m_desc.m_block_size + mark_rel.X())/(float)m_desc.m_block_size));
		int west_count = ceil(abs((mark_size / 2.0f - mark_rel.X())/(float)m_desc.m_block_size));
		int north_count = ceil(abs(((mark_size / 2.0f - mark_rel.Y())/(float)m_desc.m_block_size)));
		int south_count = ceil(abs(((mark_size / 2.0f - (float)m_desc.m_block_size + mark_rel.Y())/(float)m_desc.m_block_size)));

		//	initiate async loading of not cached data
		bool is_valid = true;
		for (int x = std::max(0, cell.X() - west_count); x <= std::min(terrain->GetNumBlocks()-1, cell.X() + east_count); ++x)
		{
			for (int y = std::max(0, cell.Y() - north_count); y <= std::min(terrain->GetNumBlocks(), cell.Y() + south_count); ++y)
			{
				if (x >= 0 && x < terrain->GetNumBlocks() 
					&& y >= 0 && y < terrain->GetNumBlocks() )
				{
					auto cell = terrain->GetCell(x, y);
					//	check is cell data is value
					if (!cell->GetDataCached().IsValid())
					{
						//	if not valid, than we can't create view
						is_valid = false;
						//	check if data is in loading state
						if (!cell->IsLoading())
						{
							//	if not than create a new task for loading for streaming module
							cell->InitiateLoading();						
							TerrainLoader* loader = new TerrainLoader(m_desc.m_map_name, Math::ivec2(x, y));
							TerrainProcessor* processor = new TerrainProcessor(cell);
							System::AsyncLoader::Instance()->AddWorkItem(loader, processor, 0);
						}
					}
				}
			}
		}

		//	if not all cell are in memory return false
		if (!is_valid)
			return System::STREAM_TRY_AGAIN;

		float* dst_buffer = (float*)m_desc.m_buffer;
		memset(dst_buffer, 0, m_desc.m_buffer_size);
		//	copy data to view
		for (int ix = std::max(0, cell.X() - west_count); ix <= std::min(terrain->GetNumBlocks()-1, cell.X() + east_count); ++ix)
		{
			for (int iy = std::max(0, cell.Y() - north_count); iy <= std::min(terrain->GetNumBlocks(), cell.Y() + south_count); ++iy)
			{
				System::Proxy<TerrainData> cell_ref;
				if (ix >= 0 && ix < terrain->GetNumBlocks() 
					&& iy >= 0 && iy < terrain->GetNumBlocks() )
				{
					cell_ref = terrain->GetCell(ix, iy)->GetDataCached();
				}				
				int src_start_x = std::max((int)0, int(mark.X() - mark_size / 2	- ix * m_desc.m_block_size));
				int src_end_x = std::min(int(m_desc.m_block_size), int(mark.X() + mark_size / 2 - ix * m_desc.m_block_size));
				int src_start_y = std::max((int)0, int(mark.Y() - mark_size / 2 - iy * m_desc.m_block_size));
				int src_end_y = std::min(int(m_desc.m_block_size), int(mark.Y() + mark_size / 2 - iy * m_desc.m_block_size));

				int dst_start_x = std::max(0, int(ix * m_desc.m_block_size + src_start_x - mark.X() + (int)mark_size / 2));
				int dst_end_x = std::min((int)m_desc.m_view_size, int(src_end_x + (ix) * m_desc.m_block_size - mark.X() + mark_size / 2));
				int dst_start_y = std::max(0, int(iy * m_desc.m_block_size + src_start_y - mark.Y() + (int)mark_size / 2));
				int dst_end_y = std::min((int)m_desc.m_view_size, int(src_end_y + (iy) * m_desc.m_block_size - mark.Y() + mark_size / 2));
				
				for (int y = 0; y < dst_end_y - dst_start_y; ++y)
				{
					for (int x = 0; x < dst_end_x - dst_start_x; ++x)
					{
						int dst_x = int(m_desc.m_block_scale * float(dst_start_x + x));
						int dst_y = int(m_desc.m_block_scale * float(dst_start_y + y));
						int src_x = src_start_x + x;
						int src_y = src_start_y + y;

						if (dst_x >= 0 && dst_x < mark_size && dst_y >= 0 && dst_y < mark_size)
						{								
							if (cell_ref.IsValid())
							{
								dst_buffer[dst_x + m_desc.m_view_size * dst_y] = 20.f * cell_ref->Value(src_x, src_y, m_desc.m_block_size);
							}
							else
							{
								dst_buffer[dst_x + m_desc.m_view_size * dst_y] = 0;
							}
						}
						else
						{
							std::cout << "Index out of range" << std::endl;	
						}
					}
				}

				/*for (int i = 0; i < m_desc.m_view_size; ++i)
				{
					for (int j = 0; j < m_desc.m_view_size; ++j)
					{
						dst_buffer[j + i * m_desc.m_view_size] = pow(1.2, i);
					}
				}*/
			}
		}
				
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainViewLoader::Decompress(void** data, unsigned* size)
	{
		*data = m_desc.m_buffer;
		*size = m_desc.m_buffer_size;
		return System::STREAM_OK;
	}

	System::StreamingStepResult TerrainViewLoader::Destroy()
	{
		return System::STREAM_OK;
	}
}