#ifndef _H_PUNK_OPENCL_PLATFORM
#define _H_PUNK_OPENCL_PLATFORM

#include "../../config.h"

namespace Gpu
{
	namespace OpenCL
	{
		class PUNK_ENGINE_API Platform
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
