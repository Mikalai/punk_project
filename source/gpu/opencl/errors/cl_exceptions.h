#ifndef _H_OPENCL_EXCEPTIONS
#define _H_OPENCL_EXCEPTIONS

#include <CL/cl.h>
#include "../../../system/errors/module.h"

#define CreateOpenCLException(X) \
		class PUNK_ENGINE OpenCL_##X##_Exception : public OpenCLException \
		{ \
		public: \
		OpenCL_##X##_Exception() : OpenCLException(System::string(#X)) {} \
		OpenCL_##X##_Exception(const System::string& msg) : OpenCLException(System::string(#X) + msg) {} \
		}

namespace GPU
{
	namespace OpenCL
	{
		class PUNK_ENGINE OpenCLException : public System::PunkException
		{
		public:
			OpenCLException() : System::PunkException(L"OpenCLException") {}
			OpenCLException(const System::string& msg) : System::PunkException(msg) {}
		};

		CreateOpenCLException(CL_DEVICE_NOT_FOUND);
		CreateOpenCLException(CL_DEVICE_NOT_AVAILABLE);
		CreateOpenCLException(CL_COMPILER_NOT_AVAILABLE);
		CreateOpenCLException(CL_MEM_OBJECT_ALLOCATION_FAILURE);
		CreateOpenCLException(CL_OUT_OF_RESOURCES);
		CreateOpenCLException(CL_OUT_OF_HOST_MEMORY);
		CreateOpenCLException(CL_PROFILING_INFO_NOT_AVAILABLE);
		CreateOpenCLException(CL_MEM_COPY_OVERLAP);
		CreateOpenCLException(CL_IMAGE_FORMAT_MISMATCH);
		CreateOpenCLException(CL_IMAGE_FORMAT_NOT_SUPPORTED);
		CreateOpenCLException(CL_BUILD_PROGRAM_FAILURE);
		CreateOpenCLException(CL_MAP_FAILURE);
		CreateOpenCLException(CL_MISALIGNED_SUB_BUFFER_OFFSET);
		CreateOpenCLException(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST);
		CreateOpenCLException(CL_INVALID_VALUE);
		CreateOpenCLException(CL_INVALID_DEVICE_TYPE);
		CreateOpenCLException(CL_INVALID_PLATFORM);
		CreateOpenCLException(CL_INVALID_DEVICE);
		CreateOpenCLException(CL_INVALID_CONTEXT);
		CreateOpenCLException(CL_INVALID_QUEUE_PROPERTIES);
		CreateOpenCLException(CL_INVALID_COMMAND_QUEUE);
		CreateOpenCLException(CL_INVALID_HOST_PTR);
		CreateOpenCLException(CL_INVALID_MEM_OBJECT);
		CreateOpenCLException(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR);
		CreateOpenCLException(CL_INVALID_IMAGE_SIZE);
		CreateOpenCLException(CL_INVALID_SAMPLER);
		CreateOpenCLException(CL_INVALID_BINARY);
		CreateOpenCLException(CL_INVALID_BUILD_OPTIONS);
		CreateOpenCLException(CL_INVALID_PROGRAM);
		CreateOpenCLException(CL_INVALID_PROGRAM_EXECUTABLE);
		CreateOpenCLException(CL_INVALID_KERNEL_NAME);
		CreateOpenCLException(CL_INVALID_KERNEL_DEFINITION);
		CreateOpenCLException(CL_INVALID_KERNEL);
		CreateOpenCLException(CL_INVALID_ARG_INDEX);
		CreateOpenCLException(CL_INVALID_ARG_VALUE);
		CreateOpenCLException(CL_INVALID_ARG_SIZE);
		CreateOpenCLException(CL_INVALID_KERNEL_ARGS);
		CreateOpenCLException(CL_INVALID_WORK_DIMENSION);
		CreateOpenCLException(CL_INVALID_WORK_GROUP_SIZE);
		CreateOpenCLException(CL_INVALID_WORK_ITEM_SIZE);
		CreateOpenCLException(CL_INVALID_GLOBAL_OFFSET);
		CreateOpenCLException(CL_INVALID_EVENT_WAIT_LIST);
		CreateOpenCLException(CL_INVALID_EVENT);
		CreateOpenCLException(CL_INVALID_OPERATION);
		CreateOpenCLException(CL_INVALID_GL_OBJECT);
		CreateOpenCLException(CL_INVALID_BUFFER_SIZE);
		CreateOpenCLException(CL_INVALID_MIP_LEVEL);
		CreateOpenCLException(CL_INVALID_GLOBAL_WORK_SIZE);
	}
}

#endif	//	_H_OPENCL_EXCEPTIONS