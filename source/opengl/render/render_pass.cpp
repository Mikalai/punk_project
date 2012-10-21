#include "render_pass.h"
#include "render_target.h"
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
			TextureContext* textures = it->first;
			//if (textures)
			//	textures->Bind();

			for (auto renders = it->second.begin(); renders != it->second.end(); ++renders)
			{
				for (auto batch_it = renders->second.begin(); batch_it != renders->second.end(); ++batch_it)
				{				
					Batch* batch = *batch_it;
					int slot = 0;
					if (textures)
					{
						for each (const auto texture in batch->m_textures)
						{
							textures->SetTexture(slot, texture);
							slot++;
						}
						textures->Bind();
					}

					DummyRenderPolicy* cur_policy = renders->first;
					cur_policy->Begin();
					cur_policy->BindParameters(*(batch->m_parameters));
					batch->m_renderable->Bind(cur_policy->GetRequiredAttributesSet());
					batch->m_renderable->Render();
					batch->m_renderable->Unbind();
				}
			}

			if (textures)
				textures->Unbind();
		}
		m_render_target->Deactivate();
	}

	void RenderPass::AddBatch(TextureContext* textures, DummyRenderPolicy* policy, Batch* batch)
	{
		m_batches[textures][policy].push_back(batch);
	}

	RenderPass::~RenderPass()
	{
		for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
		{
			for (auto renders = it->second.begin(); renders != it->second.end(); ++renders)
			{
				for (auto batch_it = renders->second.begin(); batch_it != renders->second.end(); ++batch_it)
				{				
					Batch* batch = *batch_it;
					delete batch;
				}
			}
			delete it->first;
		}
	}
}