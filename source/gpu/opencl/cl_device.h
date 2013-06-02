#ifndef _H_PUNK_OPENCL_DEVICE
#define _H_PUNK_OPENCL_DEVICE

#include "../../config.h"
#include <memory>

namespace GPU
{
	namespace OpenCL
	{
		class Platform;

		class PUNK_ENGINE_API Device
		{
		public:
			Device();
			Device(const Device&);
			Device& operator = (const Device&);
			~Device();

			bool Init(Platform& value);

			struct DeviceImpl;
			DeviceImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_DEVICE
