#ifndef _H_PUNK_OPENCL_DEVICE
#define _H_PUNK_OPENCL_DEVICE

#include "../config.h"
#include <memory>

namespace OpenCL
{
	class Platform;

	class PUNK_ENGINE Device
	{
	public:
		Device();
		Device(const Device&);
		Device& operator = (const Device&);
		~Device();

		bool Init(Platform& value);

		struct DeviceImpl;
		std::unique_ptr<DeviceImpl> m_impl;
	};
}

#endif	//	_H_PUNK_OPENCL_DEVICE