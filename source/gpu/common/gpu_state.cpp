#include "gpu_state.h"
#include "texture/texture2d_array.h"

namespace Gpu
{

    BatchState::BatchState()
    {
        m_terrain_level = 0;
        m_terrain_i = 0;
        m_terrain_j = 0;
        m_terrain_slices = 0;
        m_used_bones_count = -1;
        m_cast_shadows = true;
        m_receive_shadows = true;
    }

	TextureState::TextureState()
	{
		m_normal_map = nullptr;
		m_height_map = nullptr;
		m_specular_map = nullptr;
		m_text_map = nullptr;
	}

	RenderState::RenderState()
	{
		m_clear_color.Set(0,0,0,1);
		m_line_width = 1;
		m_point_size = 1;
		m_clear_depth = 1;
		m_depth_test = true;
        m_render_depth = false;
		m_enable_lighting = false;
		m_enable_diffuse_shading = true;
        m_enable_bounding_box_rendering = false;
        m_enable_bounding_sphere_rendering= false;
        m_enable_navi_mesh_rendering = false;
        m_enable_font_rendering = false;
        m_enable_shadows = false;
        m_shadow_model = ShadowModel::ShadowMapSimple;
        m_shadow_map_size.Set(512, 512);

       // m_enable_bump_maping_shading = false;
	}

    LightState::LightState()
    {
        m_used_lights = 1;
    }

	CoreState::CoreState()
	{
		view_state = new ViewState;
		light_state = new LightState;
		render_state = new RenderState;
		batch_state = new BatchState;
		texture_state = new TextureState;

		m_active_rendering = false;
		m_color_buffer = nullptr;
		m_depth_buffer = nullptr;
		m_color_buffer = nullptr;
        m_depth_buffer = nullptr;
        m_shadow_maps = nullptr;
	}

	CoreState::CoreState(unsigned mode, CoreState *state)
	{
		if (mode & VIEW_STATE)
			view_state = new ViewState(*state->view_state);
		else
			(view_state = state->view_state, view_state->Inc());

		if (mode & LIGHT_STATE)
			light_state = new LightState(*state->light_state);
		else
			(light_state = state->light_state, light_state->Inc());

		if (mode & RENDER_STATE)
			render_state = new RenderState(*state->render_state);
		else
			(render_state = state->render_state, render_state->Inc());

		if (mode & BATCH_STATE)
			batch_state = new BatchState(*state->batch_state);
		else
			(batch_state = state->batch_state, batch_state->Inc());

		if (mode & TEXTURE_STATE)
			texture_state = new TextureState(*state->texture_state);
		else
			(texture_state = state->texture_state, texture_state->Inc());

        m_shadow_maps = state->m_shadow_maps;
	}

	CoreState::~CoreState()
	{
		if (!view_state->Dec())
			delete view_state;
		if (!light_state->Dec())
			delete light_state;
		if (!render_state->Dec())
			delete render_state;
		if (!batch_state->Dec())
			delete batch_state;
		if (!texture_state->Dec())
			delete texture_state;
	}

	CoreState* CoreState::Clone(unsigned mode)
	{		
		CoreState* state = new CoreState(mode, this);
		return state;
	}
}
