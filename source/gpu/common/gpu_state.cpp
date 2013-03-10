#include "gpu_state.h"

namespace GPU
{
	CoreState::CoreState()
	{
		m_line_width = 1;
		m_point_size = 1;
		m_depth_test = true;		
	}

	CoreState::~CoreState()
	{
		//	do not delete pointers, because they are owned by someone else
	}

	CoreState* CoreState::Clone()
	{
		return new CoreState(*this);
	}
}
