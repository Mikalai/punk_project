#include "abstract_render_context_policy.h"
#include "../error/module.h"

namespace GPU
{
	AbstractRenderPolicy::AbstractRenderPolicy()
		: m_was_modified(false)
		, m_vertex_attributes(COMPONENT_NONE)
	{}

	AbstractRenderPolicy::~AbstractRenderPolicy()
	{
	}
}
