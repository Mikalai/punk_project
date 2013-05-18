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
        m_rendering = false;
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
        Top()->m_clear_color = value;
    }

	void Frame::SetClearColor(float r, float g, float b, float a)
	{
		Top()->m_clear_color.Set(r, g, b, a);
	}

	void Frame::SetClearDepth(float value)
	{
		Top()->m_clear_depth = value;
	}

	void Frame::Clear(bool color, bool depth, bool stencil)
	{
		m_driver->SetClearColor(Top()->m_clear_color);
		m_driver->SetClearDepth(Top()->m_clear_depth);
		m_driver->Clear(color, depth, stencil);
	}

	const Math::vec4 Frame::GetClearColor() const
    {
        return Top()->m_clear_color;
    }

	void Frame::BeginRendering()
	{
        if (m_rendering)
            throw System::PunkException(L"Rendering is already started. Call EndRendering() before");        
        m_rendering = true;
		m_driver->SetRenderTarget(Top()->m_color_buffer, Top()->m_depth_buffer);
	}

	void Frame::Render(Renderable* value, bool destroy)
	{
        Batch* batch = new Batch;
		batch->m_renderable = value;
		batch->m_state = m_state.top()->Clone();
		batch->m_destroy = destroy;
		m_batches.push_back(batch);
	}

	void Frame::PushState()
	{
		m_state.push(m_state.top()->Clone());
	}

	void Frame::PopState()
	{
		delete m_state.top();
		m_state.pop();
	}

	void Frame::SetWorldMatrix(const Math::mat4& value)
	{
		Top()->m_world = value;
	}

	void Frame::MultWorldMatrix(const Math::mat4& value)
	{
		Top()->m_world *= value;
	}

	void Frame::SetViewMatrix(const Math::mat4& value)
	{
		Top()->m_view = value;
	}

	void Frame::SetProjectionMatrix(const Math::mat4& value)
	{
		Top()->m_projection = value;
	}

	void Frame::SetDiffuseColor(const Math::vec4& value)
	{
		Top()->m_diffuse_color = value;
	}

	void Frame::SetDiffuseColor(float r, float g, float b, float a)
	{
		Top()->m_diffuse_color.Set(r, g, b, a);
	}

	void Frame::SetDiffuseMap0(const Texture2D* value)
	{
		Top()->m_diffuse_map_0 = value;
	}

	void Frame::SetDiffuseMap1(const Texture2D* value)
	{
		Top()->m_diffuse_map_1 = value;
	}

	void Frame::SetFontMap(const Texture2D* value)
	{
		Top()->m_text_map = value;
	}

	void Frame::EnableDiffuseShading(bool value)
	{
		Top()->m_enable_diffuse_shading = value;
	}

	void Frame::EnableSkinning(bool value)
	{
		Top()->m_enable_skinning = value;
	}

	void Frame::SetBoneMatrix(int bone_index, const Math::mat4& value)
	{
		Top()->m_bone_matrix[bone_index] = value;
	}

	void Frame::SetSpecularColor(const Math::vec4& value)
	{
		Top()->m_specular_color = value;
	}

	void Frame::SetSpecularMap(const Texture2D* value)
	{
		Top()->m_specular_map = value;
	}

	void Frame::SetBumpMap(const Texture2D* value)
	{
		Top()->m_normal_map = value;
	}

	void Frame::CastShadows(bool value)
	{
		Top()->m_cast_shadows = value;
	}

	void Frame::ReceiveShadow(bool value)
	{
		Top()->m_receive_shadows = value;
	}

	void Frame::EndRendering()
	{
		//	array of batches should be submitted to the actual rendering
        RenderPass pass(m_batches);
		pass.Run();
        m_driver->SwapBuffers();
	}

	const Math::mat4& Frame::GetWorldMatrix() const
	{
		return Top()->m_world;
	}

	const Math::mat4& Frame::GetViewMatrix() const
	{
		return Top()->m_view;
	}

	const Math::mat4& Frame::GetProjectionMatrix() const
	{
		return Top()->m_projection;
	}

	const Math::vec4& Frame::GetDiffuseColor() const
	{
		return Top()->m_diffuse_color;
	}

	const Texture2D* Frame::GetDiffuseMap0() const
	{
		return Top()->m_diffuse_map_0;
	}

	const Texture2D* Frame::GetDiffuseMap1() const
	{
		return Top()->m_diffuse_map_1;
	}

	const Math::mat4& Frame::GetBoneMatrix(int bone_index) const
	{
		return Top()->m_bone_matrix[bone_index];
	}

	const Math::vec4& Frame::GetSpecularColor() const
	{
		return Top()->m_specular_color;
	}

	const Texture2D* Frame::GetSpecularMap() const
	{
		return Top()->m_specular_map;
	}

	const Texture2D* Frame::GetBumpMap() const
	{
		return Top()->m_normal_map;
	}

	const Math::ClipSpace& Frame::GetClipSpace() const
	{
		return Top()->m_clip_space;
	}

	void Frame::EnableBlending(bool value)
	{
		Top()->m_enable_blending = value;
	}

	void Frame::EnableDepthTest(bool value)
	{
		Top()->m_depth_test = value;
	}

	void Frame::SetBlendColor(const Math::vec4& value)
	{
		Top()->m_blend_color = value;
	}

	void Frame::SetBlendColor(float r, float g, float b, float a)
	{
		Top()->m_blend_color.Set(r, g, b, a);
	}

	void Frame::SetBlendFunc(BlendFunction src, BlendFunction dst)
	{
		Top()->m_blend_src = src;
		Top()->m_blend_dst = dst;
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
		Top()->m_enable_wireframe = value;
	}

	void Frame::EnableTerrainRendering(bool value)
	{
		Top()->m_enable_terrain = value;
	}

	void Frame::EnableLighting(bool value)
	{
		Top()->m_enable_lighting = value;
	}

	void Frame::EnableTexturing(bool value)
	{
		Top()->m_enable_texture = value;
	}

	void Frame::EnableFontRendering(bool value)
	{
		Top()->m_enable_font_rendering = value;
	}

	void Frame::SetAmbientColor(float value)
	{
		Top()->m_ambient_color = value;
	}
	
	void Frame::SetClipSpace(const Math::ClipSpace& value)
	{
		Top()->m_clip_space = value;
	}
	
	void Frame::SetHeightMap(const Texture2D* value)
	{
		Top()->m_height_map = value;
	}

	void Frame::SetLineWidth(float value)
	{
		Top()->m_line_width = value;
	}

	void Frame::SetPointSize(float value)
	{
		Top()->m_point_size = value;
	}

	void Frame::SetTextureMatrix(const Math::mat4& value)
	{
		Top()->m_texture_matrix = value;
	}
	
	void Frame::SetLocalMatrix(const Math::mat4& value)
	{
		Top()->m_local = value;
	}

	void Frame::SetSpecularFactor(float value)
	{
		Top()->m_specular_factor = value;
	}

	void Frame::SetTextColor(const Math::vec4& value)
	{
		Top()->m_text_color = value;
	}

	void Frame::EnablePerVertexColor(bool value)
    {
        Top()->m_enable_vertex_color = value;
    }

	void Frame::SetLightModel(LightModel value)
	{
		Top()->m_light_model = value;
	}

	LightParameters& Frame::Light(int slot)
	{
		if (slot < MAX_LIGHTS)
			return Top()->m_lights[slot];
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
		PushState();
		RenderableBuilder b(m_driver);
		b.Begin(PrimitiveType::LINES);
		b.Vertex3fv(start);
		b.Vertex3fv(end);
		b.End();
		Renderable* r(b.ToRenderable());
		Render(r, true);
		PopState();
	}

	FogDescription& Frame::Fog()
	{
		return Top()->m_fog;
	}

	const FogDescription& Frame::Fog() const
	{
		return Top()->m_fog;
	}
}
