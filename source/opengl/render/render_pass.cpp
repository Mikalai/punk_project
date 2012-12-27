#include "render_pass.h"
#include "render_target.h"
#include "render_state.h"
#include "../textures/texture_context.h"

namespace OpenGL
{
	RenderPass::RenderPass()
	{

	}

	void RenderPass::Render()
	{		
		m_render_target->Activate();
		for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
		{
			Batch* batch = *it;					
			//if (batch->m_state->m_tc.IsValid())
			//{
			//	batch->m_state->m_tc->Bind();
			//}

			//auto cur_policy = batch->m_state->m_render_policy;
			//cur_policy->Begin();
			//cur_policy->BindParameters(batch->m_state);
			//batch->m_renderable->Bind(cur_policy->GetRequiredAttributesSet());
			//batch->m_renderable->Render();
			//batch->m_renderable->Unbind();

			//if (batch->m_state->m_tc.IsValid())
			//{
			//	batch->m_state->m_tc->Unbind();
			//}
		}
		m_render_target->Deactivate();
	}

	void RenderPass::AddBatch(Batch* batch)
	{
		m_batches.push_back(batch);
	}

	RenderPass::~RenderPass()
	{
		for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
		{
			delete *it;
		}
	}
}