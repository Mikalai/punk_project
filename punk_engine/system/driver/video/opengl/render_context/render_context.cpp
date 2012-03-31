#include "render_context.h"
#include "render_context_impl.h"
#include <algorithm>

namespace OpenGL
{
	RenderContext::RenderContext()
		: impl_rc(nullptr)
	{}

	RenderContext::RenderContext(const RenderContext& rc)
		: impl_rc(nullptr)
	{}

	RenderContext& RenderContext::operator= (const RenderContext& rc)
	{
		RenderContext temp(rc);
		std::swap(*impl_rc, *rc.impl_rc);
		return *this;
	}

	void RenderContext::Begin()
	{
		impl_rc->Begin();
	}

	void RenderContext::End()
	{
		impl_rc->End();
	}

	void RenderContext::SetFragmentShader(Shader* shader)
	{
		impl_rc->m_fragment_shader = shader;
	}

	void RenderContext::SetGeometryShader(Shader* shader)
	{
		impl_rc->m_geometry_shader = shader;
	}

	void RenderContext::SetVertexShader(Shader* shader)
	{
		impl_rc->m_vertex_shader = shader;
	}
}
