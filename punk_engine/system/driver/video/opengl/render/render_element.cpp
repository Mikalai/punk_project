#include "render_element.h"

namespace Render
{
	RenderElement::RenderElement(AbstractRender* render, void* data) : m_render(render), m_parameters(data)
	{}

	AbstractRender* RenderElement::GetRender()
	{
		return m_render;
	}

	void* RenderElement::GetParameters()
	{
		return m_parameters;
	}
}
