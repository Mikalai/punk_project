#include "batch.h"

namespace OpenGL
{
	Batch::~Batch()
	{
		delete m_parameters;
	}
}