#include "frame.h"
#include "video_driver.h"
#include "render_batch.h"
#include "render_pass.h"
#include "renderable_builder.h"
#include "primitive_type.h"

namespace GPU
{
	Frame::Frame(VideoDriver* driver)
	{
		m_driver = driver;
        m_state.push(new CoreState);
	}

	Frame::~Frame()
	{
		//	next should be delete in destructor
		while (!m_state.empty())
		{
			delete m_state.top();
			m_state.pop();
		}
	}

	void Frame::SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer)
	{
		Top()->m_color_buffer = color_buffer;
		Top()->m_depth_buffer = depth_buffer;
	}

	void Frame::SetClearColor(const Math::vec4& value)
    {
		Top()->render_state->m_clear_color = value;
    }

	void Frame::SetClearColor(float r, float g, float b, float a)
	{
		Top()->render_state->m_clear_color.Set(r, g, b, a);
	}

	void Frame::SetClearDepth(float value)
	{
		Top()->render_state->m_clear_depth = value;
	}

	void Frame::Clear(bool color, bool depth, bool stencil)
	{
		m_driver->SetClearColor(Top()->render_state->m_clear_color);
		m_driver->SetClearDepth(Top()->render_state->m_clear_depth);
		m_driver->Clear(color, depth, stencil);
	}

	const Math::vec4 Frame::GetClearColor() const
    {
		return Top()->render_state->m_clear_color;
    }

	void Frame::BeginRendering()
	{
		if (Top()->m_active_rendering)
            throw System::PunkException(L"Rendering is already started. Call EndRendering() before");        
		Top()->m_active_rendering = true;
		m_driver->SetRenderTarget(Top()->m_color_buffer, Top()->m_depth_buffer);
	}

	void Frame::Render(Renderable* value, bool destroy)
	{
        Batch* batch = new Batch;
		batch->m_renderable = value;
        batch->m_state = m_state.top()->Clone(CoreState::ALL_STATES);
		batch->m_destroy = destroy;
		m_batches.push_back(batch);
	}

	void Frame::PushAllState()
	{
		m_state.push(m_state.top()->Clone(CoreState::ALL_STATES));
	}

	void Frame::PopAllState()
	{
        if (!m_state.top()->Dec())
            delete m_state.top();
		m_state.pop();
	}

	void Frame::PushViewState()
	{
        CoreState* state = m_state.top();
        state = state->Clone(CoreState::VIEW_STATE);
        m_state.push(state);
	}

	void Frame::PopViewState()
	{
		PopAllState();
	}

	void Frame::PushLightState()
	{
		m_state.push(m_state.top()->Clone(CoreState::LIGHT_STATE));
	}

	void Frame::PopLightState()
	{
		PopAllState();
	}

	void Frame::PushRenderState()
	{
		m_state.push(m_state.top()->Clone(CoreState::RENDER_STATE));
	}

	void Frame::PopRenderState()
	{
		PopAllState();
	}

	void Frame::PushBatchState()
	{
		m_state.push(m_state.top()->Clone(CoreState::BATCH_STATE));
	}

	void Frame::PopBatchState()
	{
		PopAllState();
	}

	void Frame::PushTextureState()
	{
		m_state.push(m_state.top()->Clone(CoreState::TEXTURE_STATE));
	}

	void Frame::PopTextureState()
	{
		PopAllState();
	}

	void Frame::SetWorldMatrix(const Math::mat4& value)
	{
		Top()->batch_state->m_world = value;
	}

	void Frame::MultWorldMatrix(const Math::mat4& value)
	{
		Top()->batch_state->m_world *= value;
	}

	void Frame::SetViewMatrix(const Math::mat4& value)
	{
		Top()->view_state->m_view = value;
	}

	void Frame::SetProjectionMatrix(const Math::mat4& value)
	{
		Top()->view_state->m_projection = value;
	}

	void Frame::SetDiffuseColor(const Math::vec4& value)
	{
		Top()->batch_state->m_material.m_diffuse_color = value;
	}

	void Frame::SetDiffuseColor(float r, float g, float b, float a)
	{
		Top()->batch_state->m_material.m_diffuse_color.Set(r, g, b, a);
	}

	void Frame::SetDiffuseMap0(const Texture2D* value)
	{
		Top()->texture_state->m_diffuse_map_0 = value;
	}

    void Frame::SetNormalMap(const Texture2D* value)
    {
        Top()->texture_state->m_normal_map = value;
    }

	void Frame::SetDiffuseMap1(const Texture2D* value)
	{
		Top()->texture_state->m_diffuse_map_1 = value;
	}

	void Frame::SetFontMap(const Texture2D* value)
	{
		Top()->texture_state->m_text_map = value;
	}

	void Frame::EnableDiffuseShading(bool value)
	{
		Top()->render_state->m_enable_diffuse_shading = value;
	}

//    void Frame::EnableBumpMapping(bool value)
//    {
//        Top()->render_state->m_enable_bump_maping_shading = value;
//    }

	void Frame::EnableSkinning(bool value)
	{
		Top()->render_state->m_enable_skinning = value;
	}

	void Frame::SetBoneMatrix(int bone_index, const Math::mat4& value)
	{
		Top()->batch_state->m_bone_matrix[bone_index] = value;
	}

	void Frame::SetSpecularColor(const Math::vec4& value)
	{
		Top()->batch_state->m_material.m_specular_color = value;
	}

	void Frame::SetSpecularMap(const Texture2D* value)
	{
		Top()->texture_state->m_specular_map = value;
	}

	void Frame::SetBumpMap(const Texture2D* value)
	{
		Top()->texture_state->m_normal_map = value;
	}

	void Frame::CastShadows(bool value)
	{
		Top()->batch_state->m_cast_shadows = value;
	}

	void Frame::ReceiveShadow(bool value)
	{
		Top()->batch_state->m_receive_shadows = value;
	}

	void Frame::EndRendering()
	{
		//	array of batches should be submitted to the actual rendering
		RenderPass pass(m_driver, m_batches);
		pass.Run();
        m_driver->SwapBuffers();
		Top()->m_active_rendering = false;
	}

	const Math::mat4& Frame::GetWorldMatrix() const
	{
		return Top()->batch_state->m_world;
	}

	const Math::mat4& Frame::GetViewMatrix() const
	{
		return Top()->view_state->m_view;
	}

	const Math::mat4& Frame::GetProjectionMatrix() const
	{
		return Top()->view_state->m_projection;
	}

	const Math::vec4& Frame::GetDiffuseColor() const
	{
		return Top()->batch_state->m_material.m_diffuse_color;
	}

	const Texture2D* Frame::GetDiffuseMap0() const
	{
		return Top()->texture_state->m_diffuse_map_0;
	}

	const Texture2D* Frame::GetDiffuseMap1() const
	{
		return Top()->texture_state->m_diffuse_map_1;
	}

	const Math::mat4& Frame::GetBoneMatrix(int bone_index) const
	{
		return Top()->batch_state->m_bone_matrix[bone_index];
	}

	const Math::vec4& Frame::GetSpecularColor() const
	{
		return Top()->batch_state->m_material.m_specular_color;
	}

	const Texture2D* Frame::GetSpecularMap() const
	{
		return Top()->texture_state->m_specular_map;
	}

	const Texture2D* Frame::GetBumpMap() const
	{
		return Top()->texture_state->m_normal_map;
	}

	const Math::ClipSpace& Frame::GetClipSpace() const
	{
		return Top()->view_state->m_clip_space;
	}

	void Frame::EnableBlending(bool value)
	{
		Top()->render_state->m_enable_blending = value;
	}

	void Frame::EnableDepthTest(bool value)
	{
		Top()->render_state->m_depth_test = value;
	}

	void Frame::SetBlendColor(const Math::vec4& value)
	{
		Top()->render_state->m_blend_color = value;
	}

	void Frame::SetBlendColor(float r, float g, float b, float a)
	{
		Top()->render_state->m_blend_color.Set(r, g, b, a);
	}

	void Frame::SetBlendFunc(BlendFunction src, BlendFunction dst)
	{
		Top()->render_state->m_blend_src = src;
		Top()->render_state->m_blend_dst = dst;
	}
	
	//void Frame::EnableSpecularShading(bool value)
	//{
	//	Top()->m_enable_specular_shading = value;
	//}

	//void Frame::EnableBumpMapping(bool value)
	//{
	//	Top()->m_enable_bump_mapping = value;
	//}
		
	//void Frame::EnableDiffuseShading(bool value)
	//{
	//	Top()->m_enable_diffuse_shading = value;
	//}

	//void Frame::EnableSkinning(bool value)
	//{
	//	Top()->m_enable_skinning = value;
	//}

	void Frame::EnableWireframe(bool value)
	{
		Top()->render_state->m_enable_wireframe = value;
	}

	void Frame::EnableTerrainRendering(bool value)
	{
		Top()->render_state->m_enable_terrain = value;
	}

	void Frame::EnableLighting(bool value)
	{
		Top()->render_state->m_enable_lighting = value;
	}

	void Frame::EnableTexturing(bool value)
	{
		Top()->render_state->m_enable_texture = value;
	}

	void Frame::EnableFontRendering(bool value)
	{
		Top()->render_state->m_enable_font_rendering = value;
	}

	void Frame::SetAmbientColor(float value)
	{
		Top()->batch_state->m_material.m_ambient_color = value;
	}
	
	void Frame::SetClipSpace(const Math::ClipSpace& value)
	{
		Top()->view_state->m_clip_space = value;
	}
	
	void Frame::SetHeightMap(const Texture2D* value)
	{
		Top()->texture_state->m_height_map = value;
	}

	void Frame::SetLineWidth(float value)
	{
		Top()->render_state->m_line_width = value;
	}

	void Frame::SetPointSize(float value)
	{
		Top()->render_state->m_point_size = value;
	}

	void Frame::SetTextureMatrix(const Math::mat4& value)
	{
		Top()->batch_state->m_texture_matrix = value;
	}
	
	void Frame::SetLocalMatrix(const Math::mat4& value)
	{
		Top()->batch_state->m_local = value;
	}

	void Frame::SetSpecularFactor(float value)
	{
		Top()->batch_state->m_material.m_specular_factor = value;
	}

	void Frame::SetTextColor(const Math::vec4& value)
	{
		Top()->batch_state->m_material.m_text_color = value;
	}

	void Frame::EnablePerVertexColor(bool value)
    {
		Top()->render_state->m_enable_vertex_color = value;
    }

	void Frame::SetLightModel(LightModel value)
	{
		Top()->light_state->m_light_model = value;
	}

	LightParameters& Frame::Light(int slot)
	{
		if (slot < MAX_LIGHTS)
			return Top()->light_state->m_lights[slot];
		throw System::PunkException(L"Too many light");
	}

	CoreState* Frame::Top()
	{
		return m_state.top();
	}

	const CoreState* Frame::Top() const
	{
		return m_state.top();
	}

	void Frame::DrawLine(const Math::vec3& start, const Math::vec3& end)
	{
		PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
		RenderableBuilder b(m_driver);
		b.Begin(PrimitiveType::LINES);
		b.Vertex3fv(start);
		b.Vertex3fv(end);
		b.End();
		Renderable* r(b.ToRenderable());
		Render(r, true);
		PopAllState();
	}

    void Frame::DrawLine(float x1, float y1, float x2, float y2)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        SetProjectionMatrix(Math::mat4::CreateIdentity());
        SetViewMatrix(Math::mat4::CreateIdentity());
        SetWorldMatrix(Math::mat4::CreateIdentity());

        float width = GetVideoDriver()->GetWindow()->GetWidth();
        float height = GetVideoDriver()->GetWindow()->GetHeight();

        Math::vec3 p1;
        p1[0] = -1.0f + 2.0f * x1 / width;
        p1[1] = -1.0f + 2.0f * y1 / height;
        p1[2] = 0;

        Math::vec3 p2;
        p2[0] = -1.0f + 2.0f * x2 / width;
        p2[1] = -1.0f + 2.0f * y2 / height;
        p2[2] = 0;

        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::LINES);
        b.Vertex3fv(p1);
        b.Vertex3fv(p2);
        b.End();
        Renderable* r(b.ToRenderable());
        Render(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(float x, float y)
    {
        PushAllState();
        SetProjectionMatrix(Math::mat4::CreateIdentity());
        SetViewMatrix(Math::mat4::CreateIdentity());
        SetWorldMatrix(Math::mat4::CreateIdentity());

        float width = GetVideoDriver()->GetWindow()->GetWidth();
        float height = GetVideoDriver()->GetWindow()->GetHeight();

        Math::vec3 p1;
        p1[0] = -1.0f + 2.0f * x / width;
        p1[1] = -1.0f + 2.0f * y / height;
        p1[2] = 0;

        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(p1);
        b.End();
        Renderable* r(b.ToRenderable());
        Render(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(float x, float y, float z)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(Math::vec3(x, y, z));
        b.End();
        Renderable* r(b.ToRenderable());
        Render(r, true);
        PopAllState();
    }

    void Frame::DrawPoint(const Math::vec3& v)
    {
        PushAllState();
        EnableLighting(false);
        EnableTexturing(false);
        RenderableBuilder b(m_driver);
        b.Begin(PrimitiveType::POINTS);
        b.Vertex3fv(v);
        b.End();
        Renderable* r(b.ToRenderable());
        Render(r, true);
        PopAllState();
    }

	FogDescription& Frame::Fog()
	{
		return Top()->render_state->m_fog;
	}

	const FogDescription& Frame::Fog() const
	{
		return Top()->render_state->m_fog;
	}

    VideoDriver* Frame::GetVideoDriver() const
    {
        return m_driver;
    }
}
