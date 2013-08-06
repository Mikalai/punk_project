#include "abstract_render_context_policy.h"
#include "../error/module.h"

namespace Gpu
{
	AbstractRenderPolicy::AbstractRenderPolicy()
		: m_was_modified(false)
        , m_vertex_attributes(VertexComponent::NoComponent::Value())
	{}

	AbstractRenderPolicy::~AbstractRenderPolicy()
	{
	}
}
