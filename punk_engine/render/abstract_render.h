#ifndef _H_PUNK_ABSTRACT_RENDER
#define _H_PUNK_ABSTRACT_RENDER

#include "../system/allocator.h"
namespace Render
{
	class AbstractRender
	{
	public:
		virtual void Render(void* parameters) = 0;
	};
}

#endif