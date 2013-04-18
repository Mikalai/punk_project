#ifndef _H_PUNK_OPENCL_PLATFORM
#define _H_PUNK_OPENCL_PLATFORM

#include "../../config.h"

namespace GPU
{
	namespace OpenCL
	{
		class PUNK_ENGINE Platform
		{
		public:
			Platform();
			Platform(const Platform& value);
			Platform& operator = (const Platform& value);
			~Platform();

			bool Init();

			struct PlatformImpl;
			PlatformImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_PLATFORM
