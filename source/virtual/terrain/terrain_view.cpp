#include "../../system/streaming/module.h"
#include "../../gpu/opengl/textures/texture2d.h"
#include "terrain_view_loader.h"
#include "terrain_view_processor.h"
#include "terrain_manager.h"
#include "terrain_view.h"

namespace Virtual
{
	TerrainView::TerrainView(const TerrainViewDesc& desc)
		: m_desc(desc)
		, m_front_buffer((void*)new float[m_desc.view_size*m_desc.view_size])
		, m_back_buffer((void*)new float[m_desc.view_size*m_desc.view_size])
		, m_height_map_front(new GPU::OpenGL::Texture2D())
		, m_height_map_back(new GPU::OpenGL::Texture2D())
		, m_loading(false)
		, m_init(false)
	{
		memset(m_front_buffer, 0, sizeof(m_desc.view_size*m_desc.view_size*sizeof(float)));
		m_last_unprocessed.Set(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
		m_position_back = m_desc.position;
		UpdatePosition(m_desc.position);
	}

	TerrainView::~TerrainView()
	{
		delete[] m_front_buffer;
		m_front_buffer = nullptr;
		delete[] m_back_buffer;
		m_back_buffer =  nullptr;

		delete m_height_map_back;
		delete m_height_map_front;
	}

	void TerrainView::UpdatePosition(const Math::vec2& value)
	{
		//	save last update position
		m_last_unprocessed.Set(floor(value.X()), floor(value.Y()));
		//	check thrshold for uploading
		if (!m_init || !m_loading && (m_desc.position - m_last_unprocessed).Length() >= m_desc.threshold)
		{
			m_init = true;
			//	Start uploading if position is far from previos one
			InitiateAsynchronousUploading();			
		}
	}

	void TerrainView::InitiateAsynchronousUploading()
	{
		//	check if terrain view is already in update state
		if (!m_loading)
		{
			m_loading = true;
			//	swap front and back buffers
		
			std::swap(m_front_buffer, m_back_buffer);
			std::swap(m_height_map_front, m_height_map_back);
			m_desc.position = m_position_back;

			//	if not, than store position for future view
			m_position_back = m_last_unprocessed;

			TerrainViewLoaderDesc loader_desc;
			loader_desc.m_block_scale = m_desc.block_scale;
			loader_desc.m_block_size = m_desc.block_size;
			loader_desc.m_buffer = m_back_buffer;
			loader_desc.m_buffer_size = m_desc.view_size*m_desc.view_size*sizeof(float);
			loader_desc.m_view_point = m_position_back;
			loader_desc.m_view_size = m_desc.view_size;
			loader_desc.m_world_origin = m_desc.manager->GetTerrain()->GetOrigin();
			loader_desc.m_map_name = m_desc.manager->GetCurrentMap();
			loader_desc.m_manager = m_desc.manager;
			TerrainViewLoader* loader = new TerrainViewLoader(loader_desc);

			TerrainViewProcessorDesc proc_desc;
			proc_desc.m_height_map = m_height_map_back;
			proc_desc.OnEnd = OnEnd;
			proc_desc.m_view_size = m_desc.view_size;
			proc_desc.m_on_end_data = this;
			TerrainViewProcessor* processor = new TerrainViewProcessor(proc_desc);

			System::AsyncLoader::Instance()->AddWorkItem(loader, processor, &m_result);						
		}
	}

	/**
	*	This callback is called from the same thread as InitiateAsynchronousUploading, and any other rendering
	*	staff, thus no synchronization required
	*/
	void TerrainView::OnEnd(void* data)
	{
		TerrainView* view = (TerrainView*)(data);
		////	swap front and back buffers
		//std::swap(view->m_front_buffer, view->m_back_buffer);
		//std::swap(view->m_height_map_front, view->m_height_map_back);
		////	mark loading as finished
		view->m_loading = false;
		////	check if uploading is needed again
		//if ((view->m_position - view->m_last_unprocessed).Length() > view->m_threshold)
		//{
		//	view->InitiateAsynchronousUploading();
		//}
	}	
}