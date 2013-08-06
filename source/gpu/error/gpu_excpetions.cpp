#include "gpu_exceptions.h"

namespace Gpu
{
	GPUException::GPUException()
		: System::PunkException(L"GPUException")
	{}

	GPUException::GPUException(const System::string& msg)
		: System::PunkException(msg)
	{}
}