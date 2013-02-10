#include "module.h"

namespace GPU
{
	bool GPU_INIT(const Config& data)
	{
		bool flag = true;
		flag &= GPU_COMMON_INIT(data);
		flag &= OpenGL::GPU_OPENGL_INIT(data);
		return flag;
	}

	bool GPU_DESTROY()
	{
		OpenGL::GPU_OPENGL_DESTROY();
		return true;
	}

}