/*
File: RenderElement.h
Author: Abramau Mikalai
Description: Abstract class of any element supposed to be rendered
*/

#ifndef _H_RENDER_ELEMENT
#define _H_RENDER_ELEMENT

#include "../system/allocator.h"
#include "render.h"
#include "../math/mat4.h"
#include "../common/attachable_object.h"
#include "../driver/video/driver.h"
#include "../driver/video/driver.h"
#include "../math/mat4.h"

namespace Render
{
    class RenderElement
    {
		AbstractRender* m_render;
		void* m_parameters;

		RenderElement(const RenderElement&);
		RenderElement& operator = (const RenderElement&);

	public:
		RenderElement(AbstractRender* render, void* data);
		AbstractRender* GetRender();
		void* GetParameters();
    };
}

#endif //_H_RENDER_ELEMENT
