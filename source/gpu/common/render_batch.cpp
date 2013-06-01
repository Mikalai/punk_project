#include "render_batch.h"
#include "gpu_state.h"
#include "renderable.h"

namespace GPU
{
	Batch::~Batch()
	{
		delete m_state;
		m_state = nullptr;
		if (m_destroy)
		{
			delete m_renderable;
			m_renderable = nullptr;
		}
	}
}
