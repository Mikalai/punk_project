#ifndef _H_PUNK_OPENCL_PROGRAM_IMPL
#define _H_PUNK_OPENCL_PROGRAM_IMPL

#include <CL/opencl.h>
#include "program.h"
#include "../system/logger.h"
#include "../string/string.h"
#include "../system/buffer.h"
#include "../system/binary_file.h"

#include "kernel_impl.h"

namespace OpenCL
{
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
				if (error != CL_SUCCESS)
					return (out_error() << "Can't release OpenCL program" << std::endl, false);
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
			if (error != CL_SUCCESS)
				return (out_error() << "Can't create kernel " << name << " from program" << std::endl, false);
			
			return true;
		}

		bool CreateFromFile(const System::string& path)
		{
			Clear();

			System::Buffer buffer;
			if (!System::BinaryFile::Load(path, buffer))
				return (out_error() << "Can't load binary file with OpenCL program" << std::endl, false);

			cl_int error;
			const void* source = buffer.StartPointer(); 
			size_t source_size = buffer.GetSize();
			m_program = clCreateProgramWithSource(m_context, 1, (const char**)&source, &source_size, &error);

			if (error != CL_SUCCESS)
				return (out_error() << "Can't create program with source" << std::endl, false);

			error = clBuildProgram(m_program, 1, &m_device, nullptr, nullptr, nullptr);
			if (error != CL_SUCCESS)
			{
				out_error() << "Can't build OpenCL program" << std::endl;
				size_t size;
				clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, 0, 0, &size);
				std::vector<char> buf(size);
				error = clGetProgramBuildInfo(m_program, m_device, CL_PROGRAM_BUILD_LOG, size, &buf[0], &size);
				if (error != CL_SUCCESS)
					return (out_error() << "Can't even get error build log" << std::endl, false);
				System::string log(&buf[0], buf.size());
				out_error() << "Build log: " << std::endl << log << std::endl;
				return false;
			}
			return true;
		}
	};
}

#endif	//	_H_PUNK_OPENCL_PROGRAM_IMPL