#include "gpu_exceptions.h"

namespace GPU
{
	GPUException::GPUException()
		: System::PunkException(L"GPUException")
	{}

	GPUException::GPUException(const System::string& msg)
		: System::PunkException(msg)
	{}
}