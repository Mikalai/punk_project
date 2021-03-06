#ifndef _H_PUNK_OPENCL_CONTEXT
#define _H_PUNK_OPENCL_CONTEXT

#include "../../config.h"
#include <memory>

namespace GPU
{
	namespace OpenCL
	{
		class Device;

		struct ContextImpl;

		class PUNK_ENGINE Context
		{
		public:
			Context();
			Context(const Context&);
			Context& operator = (const Context&);
			~Context();

			bool Init(Device& device);
			
			std::unique_ptr<ContextImpl> m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_CONTEXT