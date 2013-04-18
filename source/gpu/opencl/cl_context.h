#ifndef _H_PUNK_OPENCL_CONTEXT
#define _H_PUNK_OPENCL_CONTEXT

#include "../../config.h"

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

			ContextImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_CONTEXT
