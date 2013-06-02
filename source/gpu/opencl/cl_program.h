#ifndef _H_PUNK_OPENCL_PROGRAM
#define _H_PUNK_OPENCL_PROGRAM

#include "../../config.h"
#include <memory>

namespace System { class string; }

namespace GPU
{
	namespace OpenCL
	{
		class Context;
		class Kernel;
		class Device;
		class CommandQueue;

		class PUNK_ENGINE_API Program
		{
		public:
			Program();
			Program(const Program& program);
			Program& operator = (const Program& program);
			~Program();

			bool Init(Context& context, Device& device, CommandQueue& queue);
			bool CreateFromFile(const System::string& path);
			bool GetKernel(const System::string& name, Kernel& value);

			struct ProgramImpl;
			ProgramImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_PROGRAM
