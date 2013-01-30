#include "module.h"

namespace GPU
{
	bool GPU_INIT(void* data)
	{
		bool flag = true;
		flag &= GPU_COMMON_INIT(data);
		flag &= OpenGL::GPU_OPENGL_INIT(data);
		return flag;
	}
}