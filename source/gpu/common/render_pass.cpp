#include "render_pass.h"
#include "renderable.h"
#include "render_batch.h"
#include "abstract_render_context_policy.h"
#include "render_target.h"
#include "gpu_state.h"
#include "texture2d.h"
#include "texture_context.h"

namespace GPU
{
	RenderPass::RenderPass(std::vector<Batch*> batches)
		: m_batches(batches)
	{}

	RenderPass::~RenderPass()
	{
		for (auto b : m_batches)
		{
			delete b;
		}
		m_batches.clear();
	}

	void RenderPass::Run()
	{
		TextureContext tc;
		for (auto batch : m_batches)
		{
			tc.Clear();
			AbstractRenderPolicy* policy = nullptr;
			CoreState* state = batch->m_state;
			if (state->m_enable_font_rendering)
			{
				tc.SetTexture(0, state->m_text_map);
				tc.SetTexture(1, state->m_diffuse_map_0);
				policy = AbstractRenderPolicy::find(RenderPolicySet::GUI);
			}
			else if (state->m_enable_skinning)
			{
				tc.SetTexture(0, state->m_diffuse_map_0);
				tc.SetTexture(1, state->m_normal_map);
				policy = AbstractRenderPolicy::find(RenderPolicySet::Skinning);
			}
			else if (state->m_enable_terrain)
			{
				tc.SetTexture(0, state->m_diffuse_map_0);
				tc.SetTexture(1, state->m_diffuse_map_1);
				tc.SetTexture(2, state->m_height_map);
				tc.SetTexture(3, state->m_normal_map);
				policy = AbstractRenderPolicy::find(RenderPolicySet::Terrain);
			}
			else if (state->m_enable_lighting)
			{
				if (state->m_enable_texture)
				{
					if (state->m_enable_diffuse_shading)
					{
						if (state->m_light_model == LightModel::BumpMapping)
						{
							tc.SetTexture(0, state->m_diffuse_map_0);
							tc.SetTexture(1, state->m_normal_map);
							policy = AbstractRenderPolicy::find(RenderPolicySet::BumpMapping);
						}
						else if (state->m_light_model == LightModel::PerFragmentDiffuse)
						{
							tc.SetTexture(0, state->m_diffuse_map_0);
							policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentTextureDiffuse);
						}
						else if (state->m_light_model == LightModel::PerVertexDiffuse)
						{
							tc.SetTexture(0, state->m_diffuse_map_0);
							policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexTextureDiffuse);
						}
					}
				}
				else
				{
					if (state->m_light_model == LightModel::PerVertexDiffuse)
					{
						//	LIGHT-DIFFUSE-COLOR per Vertex
						policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexDiffuse);
					}
					else if (state->m_light_model == LightModel::PerFragmentDiffuse)
					{
						//	LIGHT-DIFFUSE-COLOR per Fragment
						policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentDiffuse);
					}
				}
			}
			else	//	NO LIGHTING
			{
				if (state->m_enable_texture)
				{
					if (state->m_enable_diffuse_shading)
					{
						policy = AbstractRenderPolicy::find(RenderPolicySet::SolidTextured3D);
						tc.SetTexture(0, state->m_diffuse_map_0);
					}
				}
				else
				{
					if (state->m_enable_diffuse_shading)
					{
						if (state->m_enable_vertex_color)
						{
							policy = AbstractRenderPolicy::find(RenderPolicySet::SolidVertexColor);
						}
						else
						{
							//	diffuse only
							policy = AbstractRenderPolicy::find(RenderPolicySet::Solid3D);
						}
					}
				}
			}

			if (policy)
			{
				Renderable* renderable = batch->m_renderable;
				tc.Bind();
				policy->Begin();
				policy->BindParameters(*state);
				renderable->Bind(policy->GetRequiredAttributesSet());
				renderable->Render();
				renderable->Unbind();
				policy->End();
				tc.Unbind();
			}
		}
	}
}
