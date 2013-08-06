#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include <stddef.h>
#include "../config.h"
#include <deque>

namespace System
{
    class PUNK_ENGINE_API Pool
	{        
	public:
        Pool();
        ~Pool();
        void* Alloc(size_t size);
        void Free(void* value);
        void Clear();
    private:
        std::deque<void*> m_free;
	};
}

#endif  //  _H_PUNK_POOL
