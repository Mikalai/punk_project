#ifndef _H_PUNK_OPENGL_RENDERABLE
#define _H_PUNK_OPENGL_RENDERABLE

#include <cstdint>
#include "../../system/smart_pointers/module.h"
#include "../error/module.h"
#include "vertex_component.h"

namespace Gpu
{
    class PUNK_ENGINE_API Renderable
	{
	public:

		Renderable();

		virtual ~Renderable() {}

        virtual void Bind(int64_t)
		{
			throw GPUException(L"Bind() not implemented");
		}

		virtual void Unbind()
		{
			throw GPUException(L"Unbind() not implemented");
		}

		virtual void Render()
		{
			throw GPUException(L"Load() not implemented");
		}

        virtual size_t GetMemoryUsage()
        {
            throw GPUException(L"GetMemoryUsage() not implemented");
        }

        virtual bool HasData() const
        {
            throw GPUException(L"HasData() not implemented");
        }

	protected:

		int m_primitive_type;
	};
}

#endif	//	_H_PUNK_OPENGL_RENDERABLE
