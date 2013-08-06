#ifndef _H_PUNK_OPENCL_PROGRAM_IMPL
#define _H_PUNK_OPENCL_PROGRAM_IMPL

#ifdef USE_OPENCL
#include <CL/opencl.h>
#include "../../system/buffer.h"
#include "../../system/binary_file.h"
#include "cl_program.h"
#include "errors/module.h"
#include "cl_kernel_impl.h"
#else
#include "cl_program.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct Program::ProgramImpl
		{
			cl_program m_program;
			cl_context m_context;
			cl_device_id m_device;
			cl_command_queue m_queue;

			ProgramImpl() : m_program(0), m_context(0), m_device(0) {}

			bool Init(cl_context context, cl_device_id device, cl_command_queue queue)
			{
				Clear();
				m_context = context;
				m_device = device;
				m_queue = queue;
				return true;
			}

			bool Clear()
			{
				if (m_program)
				{
					cl_int error = clReleaseProgram(m_program);
					CHECK_CL_ERROR(error, L"Can't release OpenCL program");
				}
				return true;
			}

			~ProgramImpl()
			{
				Clear();
			}

			bool GetKernel(const System::string name, Kernel& kernel)
			{
				char buffer[2048];
				name.ToANSI(buffer, 2048);

				cl_int error;
				kernel.m_impl->m_kernel = clCreateKernel(m_program, buffer, &error);
				kernel.m_impl->m_queue = m_queue;
				CHECK_CL_ERROR(error, L"Can't create kernel " + name + L" from program");

				return true;
			}

			bool CreateFromFile(const System::string& path)
			{
				Clear();

				System::Buffer buffer;
				System::BinaryFile::Load(path, buffer);

				cl_int error;
				const void* source = buffer.StartPointer();
				size_t source_size = buffer.GetSize();
				m_program = clCreateProgramWithSource(m_context, 1, (const char**)&source, &source_size, &error);

				CHECK_CL_ERROR(error, L"Can't create program with source");

				error = clBuildProgram(m_program, 1, &m_device, nullptr, nullptr, nullptr);
				if (error != CL_SUCCESS)
				{
					size_t size;
					clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, 0, 0, &size);
					std::vector<char> buf(size);
					error = clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, size, &buf[0], &size);
					CHECK_CL_ERROR(error, L"Can't even get error build log");
					System::string log(&buf[0], buf.size());
					throw OpenCLException(log);
				}
				return true;
			}
		};
		#endif
	}
}

#endif	//	_H_PUNK_OPENCL_PROGRAM_IMPL
