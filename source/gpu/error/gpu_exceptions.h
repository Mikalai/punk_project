#ifndef _H_PUNK_GPU_EXCPETION
#define _H_PUNK_GPU_EXCPETION

#include "../../system/errors/module.h"

namespace GPU
{
	class PUNK_ENGINE GPUException : public System::PunkException
	{
	public:
		GPUException();
		GPUException(const System::string& msg);
	};
}

#endif	//	_H_PUNK_GPU_EXCPETION