#ifndef _H_PUNK_OPENCL_BUFFER
#define _H_PUNK_OPENCL_BUFFER

#include "../../config.h"

namespace Gpu
{
	namespace OpenCL
	{
		class Context;
		class CommandQueue;

		class PUNK_ENGINE_API Buffer
		{
		public:

			enum BufferType { READ_ONLY, WRITE_ONLY, READ_WRITE };

			Buffer();
			Buffer(const Buffer& buffer);
			Buffer& operator = (const Buffer& buffer);
			~Buffer();

			bool Init(Context& context, CommandQueue& queue, BufferType type, int size);

			bool Write(const void* data, int size);
			bool Read(void* data, int size);

			struct BufferImpl;
			BufferImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_BUFFER
