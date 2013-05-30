#include "render_pass.h"
#include "renderable.h"
#include "render_batch.h"
#include "abstract_render_context_policy.h"
#include "render_target.h"
#include "video_driver.h"
#include "gpu_state.h"
#include "texture2d.h"
#include "texture_context.h"

namespace GPU
{
	RenderPass::RenderPass(VideoDriver* driver, std::vector<Batch*> batches)
		: m_driver(driver)
		, m_batches(batches)
	{}

	RenderPass::~RenderPass()
	{
		for (auto b : m_batches)
		{
			delete b;
		}
		m_batches.clear();
	}

	void RenderPass::SetUpShadowMap()
    {
		auto w = m_driver->GetConfig().shadow_map_width;
		auto h = m_driver->GetConfig().shadow_map_height;
        if (!m_shadow_map)
        {
			m_shadow_map = m_driver->CreateTexture2D(w, h, ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT16, nullptr, false);
        }
        else
        {
            m_shadow_map->Resize(w, h);
        }
		m_driver->SetRenderTarget(nullptr, m_shadow_map);
		m_driver->Clear(true, true, true);
    }

    void RenderObject(Batch* b)
    {
		for (LightParameters p : b->m_state->light_state->m_lights)
        {
			//std::unique_ptr<CoreState> state(b->m_state->Clone());
        }
    }

	void RenderPass::GenerateShadowMap(std::vector<Batch*>& batches)
    {
        SetUpShadowMap();
        for (Batch* b : batches)
        {
			if (b->m_state->batch_state->m_cast_shadows)
            {
                RenderObject(b);
            }
        }
		m_driver->SetRenderTarget(nullptr, nullptr);
    }

	void RenderPass::OnePass(Renderable* renderable, CoreState* state)
    {
        TextureContext tc;
        AbstractRenderPolicy* policy = nullptr;
		if (state->render_state->m_render_depth)
		{
			policy = AbstractRenderPolicy::find(RenderPolicySet::DepthRender);
        }
		else if (state->render_state->m_enable_font_rendering)
        {
			tc.SetTexture(0, state->texture_state->m_text_map);
			tc.SetTexture(1, state->texture_state->m_diffuse_map_0);
            policy = AbstractRenderPolicy::find(RenderPolicySet::GUI);
        }
		else if (state->render_state->m_enable_skinning)
        {
			tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
			tc.SetTexture(1, state->texture_state->m_normal_map);
            policy = AbstractRenderPolicy::find(RenderPolicySet::Skinning);
        }
		else if (state->render_state->m_enable_terrain)
        {
			tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
			tc.SetTexture(1, state->texture_state->m_diffuse_map_1);
			tc.SetTexture(2, state->texture_state->m_height_map);
			tc.SetTexture(3, state->texture_state->m_normal_map);
            policy = AbstractRenderPolicy::find(RenderPolicySet::Terrain);
        }
		else if (state->render_state->m_enable_lighting)
        {
			if (!state->render_state->m_enable_shadows || !state->batch_state->m_receive_shadows)
            {
				if (state->render_state->m_enable_texture)
                {
					if (state->render_state->m_enable_diffuse_shading)
                    {
						if (state->light_state->m_light_model == LightModel::BumpMapping)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
							tc.SetTexture(1, state->texture_state->m_normal_map);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::BumpMapping);
                        }
						else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentTextureDiffuse);
                        }
						else if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexTextureDiffuse);
                        }
                    }
                }
                else
                {
					if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
                    {
                        //	LIGHT-DIFFUSE-COLOR per Vertex
                        policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexDiffuse);
                    }
					else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
                    {
                        //	LIGHT-DIFFUSE-COLOR per Fragment
                        policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentDiffuse);
                    }
                }
            }
            else
            {
				if (state->render_state->m_enable_texture)
                {
					if (state->render_state->m_enable_diffuse_shading)
                    {
						if (state->light_state->m_light_model == LightModel::BumpMapping)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
							tc.SetTexture(1, state->texture_state->m_normal_map);
                            tc.SetTexture(2, m_shadow_map);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::BumpMappingShadowing);
                        }
						else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
                            tc.SetTexture(1, m_shadow_map);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentTextureDiffuseShadowing);
                        }
						else if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
                        {
							tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
                            tc.SetTexture(1, m_shadow_map);
                            policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexTextureDiffuseShadowing);
                        }
                    }
                }
                else
                {
					if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
                    {
                        //	LIGHT-DIFFUSE-COLOR per Vertex
                        tc.SetTexture(0, m_shadow_map);
                        policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerVertexDiffuseShadowing);
                    }
					else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
                    {
                        //	LIGHT-DIFFUSE-COLOR per Fragment
                        tc.SetTexture(0, m_shadow_map);
                        policy = AbstractRenderPolicy::find(RenderPolicySet::LightPerFragmentDiffuseShadowing);
                    }
                }
            }
        }
        else	//	NO LIGHTING
        {
			if (state->render_state->m_enable_texture)
            {
				if (state->render_state->m_enable_diffuse_shading)
                {
                    policy = AbstractRenderPolicy::find(RenderPolicySet::SolidTextured3D);
					tc.SetTexture(0, state->texture_state->m_diffuse_map_0);
                }
            }
            else
            {
				if (state->render_state->m_enable_diffuse_shading)
                {
					if (state->render_state->m_enable_vertex_color)
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

	void RenderPass::Run()
	{
		//	Process batches: find all shadow casters
		//	Process batches: split batches on light groups
		//	Process batches: for each light group generate shadow map
		//	Process batches: for each light group using shadow map render final scene

        for (Batch* batch : m_batches)
		{
            OnePass(batch->m_renderable, batch->m_state);
		}
	}
}
