#ifndef _H_PUNK_OPENCL_KERNEL
#define _H_PUNK_OPENCL_KERNEL

#include "../../config.h"
#include <memory>

namespace GPU
{
	namespace OpenCL
	{
		class Buffer;

		class PUNK_ENGINE_PUBLIC Kernel
		{
		public:
			Kernel();
			Kernel(const Kernel& value);
			Kernel& operator = (const Kernel& value);
			~Kernel();

			bool Call(int elements_to_process);
			bool SetArgument(int index, Buffer& buffer);
			bool SetArgument(int index, int value);

			struct KernelImpl;
			KernelImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_KERNEL
