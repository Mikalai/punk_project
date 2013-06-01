#include "gl_batch.h"
#include "../../common/gpu_state.h"

namespace GPU
{
	namespace OpenGL
	{
		Batch::~Batch()
		{
			delete m_state;
			m_state = nullptr;
		}
	}
}