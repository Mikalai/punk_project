#include "../../system/streaming/module.h"
#include "terrain_view_loader.h"
#include "terrain_view_processor.h"

#include "terrain_view.h"

namespace Virtual
{
	TerrainView::TerrainView(const Math::vec2 position)
		: m_view_size(512)
		, m_front_buffer((void*)new float[m_view_size*m_view_size])
		, m_back_buffer((void*)new float[m_view_size*m_view_size])
		, m_threshold(128)
		, m_position(position)
	{
		memset(m_front_buffer, 0, sizeof(m_view_size*m_view_size*sizeof(float)));
	}

	TerrainView::~TerrainView()
	{
		delete[] m_front_buffer;
		m_front_buffer = nullptr;
		delete[] m_back_buffer;
		m_back_buffer =  nullptr;
	}

	void TerrainView::UpdatePosition(const Math::vec2& value)
	{
		//	save last update position
		m_last_unprocessed = value;
		//	check thrshold for uploading
		if (!m_loading && (m_position - m_last_unprocessed).SqrLength() > m_threshold*m_threshold)
		{
			//	Start uploading if position is far from previos one
			InitiateAsynchronousUploading();
		}
	}

	void TerrainView::InitiateAsynchronousUploading()
	{
		//	check if terrain view is already in update state
		if (!m_loading)
		{
			//	if not, than store position for future view
			m_position = m_last_unprocessed;
			Math::vec2 map_position = m_position;
			TerrainViewLoader* loader = new TerrainViewLoader(m_back_buffer, m_view_size*m_view_size*sizeof(float), m_view_size, map_position);
			TerrainViewProcessor* processor = new TerrainViewProcessor(m_height_map_back.Get());
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
		//	swap front and back buffers
		std::swap(m_front_buffer, m_back_buffer);
		std::swap(m_height_map_front, m_height_map_back);
		//	mark loading as finished
		m_loading = false;
		//	check if uploading is needed again
		if ((m_position - m_last_unprocessed).Length() > m_threshold)
		{
			InitiateAsynchronousUploading();
		}
	}
}