#include "abstract_render_context_policy.h"
#include "../error/module.h"

namespace GPU
{
	AbstractRenderPolicy::AbstractRenderPolicy()
		: m_was_modified(false)
		, m_vertex_attributes(VertexComponent::None::Value())
	{}

	AbstractRenderPolicy::~AbstractRenderPolicy()
	{
	}
}
