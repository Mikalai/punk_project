#include "../../common/gpu_state.h"
#include "../../../system/state_manager.h"
#include "gl_batch.h"
#include "gl_frame.h"
#include "../driver/gl_driver.h"
#include "gl_renderer.h"

namespace GPU
{
	Frame::FrameImpl::FrameImpl()
	{
		m_driver = nullptr;
	}

	Frame::FrameImpl::~FrameImpl()
	{
		//	next should be delete in destructor
		while (!m_state.empty())
		{
			delete m_state.top();
			m_state.pop();
		}
	}

	void Frame::FrameImpl::BeginRendering()
	{
		m_state.push(new CoreState);
	}

	void Frame::FrameImpl::Render(Renderable* value)
	{
		OpenGL::Batch* batch = new OpenGL::Batch;
		batch->m_renderable = value;
		batch->m_state = m_state.top()->Clone();
		m_batches.push_back(batch);
	}

	void Frame::FrameImpl::PushState()
	{
		m_state.push(m_state.top()->Clone());
	}

	void Frame::FrameImpl::PopState()
	{
		delete m_state.top();
		m_state.pop();
	}

	CoreState* Frame::FrameImpl::Top()
	{
		return m_state.top();
	}

	const CoreState* Frame::FrameImpl::Top() const
	{
		return m_state.top();
	}

	void Frame::FrameImpl::SetWorldMatrix(const Math::mat4& value)
	{
		Top()->m_world = value;
	}

	void Frame::FrameImpl::MultWorldMatrix(const Math::mat4& value)
	{
		Top()->m_world *= value;
	}

	void Frame::FrameImpl::SetViewMatrix(const Math::mat4& value)
	{
		Top()->m_view = value;
	}

	void Frame::FrameImpl::SetProjectionMatrix(const Math::mat4& value)
	{
		Top()->m_projection = value;
	}

	void Frame::FrameImpl::SetDiffuseColor(const Math::vec4& value)
	{
		Top()->m_diffuse_color = value;
	}

	void Frame::FrameImpl::SetDiffuseMap0(const Texture2D* value)
	{
		Top()->m_diffuse_map_0 = value;
	}

	void Frame::FrameImpl::SetDiffuseMap1(const Texture2D* value)
	{
		Top()->m_diffuse_map_1 = value;
	}

	void Frame::FrameImpl::EnableDiffuseShading(bool value)
	{
		Top()->m_enable_diffuse_shading = value;
	}

	void Frame::FrameImpl::EnableSkinning(bool value)
	{
		Top()->m_enable_skinning = value;
	}

	void Frame::FrameImpl::SetBoneMatrix(int bone_index, const Math::mat4& value)
	{
		Top()->m_bone_matrix[bone_index] = value;
	}

	void Frame::FrameImpl::SetSpecularColor(const Math::vec4& value)
	{
		Top()->m_specular_color = value;
	}

	void Frame::FrameImpl::SetSpecularMap(const Texture2D* value)
	{
		Top()->m_specular_map = value;
	}

	void Frame::FrameImpl::EnableSpecularShading(bool value)
	{
		Top()->m_enable_specular_shading = value;
	}

	void Frame::FrameImpl::SetBumpMap(const Texture2D* value)
	{
		Top()->m_normal_map = value;
	}

	void Frame::FrameImpl::EnableBumpMapping(bool value)
	{
		Top()->m_enable_bump_mapping = value;
	}

	void Frame::FrameImpl::CastShadows(bool value)
	{
		Top()->m_cast_shadows = value;
	}

	void Frame::FrameImpl::ReceiveShadow(bool value)
	{
		Top()->m_receive_shadows = value;
	}

	void Frame::FrameImpl::EndRendering()
	{
		//	array of batches should be submitted to the actual rendering
		OpenGL::RenderPass pass(m_batches);
		pass.Run();
		m_driver->SwapBuffers();
	}

	void Frame::FrameImpl::SetVideoDriver(VideoDriverImpl* driver)
	{
		m_driver = driver;
	}

	const Math::mat4& Frame::FrameImpl::GetWorldMatrix() const
	{
		return Top()->m_world;
	}

	const Math::mat4& Frame::FrameImpl::GetViewMatrix() const
	{
		return Top()->m_view;
	}

	const Math::mat4& Frame::FrameImpl::GetProjectionMatrix() const
	{
		return Top()->m_projection;
	}

	const Math::vec4& Frame::FrameImpl::GetDiffuseColor() const
	{
		return Top()->m_diffuse_color;
	}

	const Texture2D* Frame::FrameImpl::GetDiffuseMap0() const
	{
		return Top()->m_diffuse_map_0;
	}

	const Texture2D* Frame::FrameImpl::GetDiffuseMap1() const
	{
		return Top()->m_diffuse_map_1;
	}

	const Math::mat4& Frame::FrameImpl::GetBoneMatrix(int bone_index) const
	{
		return Top()->m_bone_matrix[bone_index];
	}

	const Math::vec4& Frame::FrameImpl::GetSpecularColor() const
	{
		return Top()->m_specular_color;
	}

	const Texture2D* Frame::FrameImpl::GetSpecularMap() const
	{
		return Top()->m_specular_map;
	}

	const Texture2D* Frame::FrameImpl::GetBumpMap() const
	{
		return Top()->m_normal_map;
	}

	const Math::ClipSpace& Frame::FrameImpl::GetClipSpace() const
	{
		return Top()->m_clip_space;
	}

	void Frame::FrameImpl::EnableBlending(bool value)
	{
		Top()->m_blending = value;
	}

	void Frame::FrameImpl::EnableDepthTest(bool value)
	{
		Top()->m_depth_test = value;
	}

	
	//void Frame::FrameImpl::EnableSpecularShading(bool value)
	//{
	//	Top()->m_enable_specular_shading = value;
	//}

	//void Frame::FrameImpl::EnableBumpMapping(bool value)
	//{
	//	Top()->m_enable_bump_mapping = value;
	//}
		
	//void Frame::FrameImpl::EnableDiffuseShading(bool value)
	//{
	//	Top()->m_enable_diffuse_shading = value;
	//}

	//void Frame::FrameImpl::EnableSkinning(bool value)
	//{
	//	Top()->m_enable_skinning = value;
	//}

	void Frame::FrameImpl::EnableWireframe(bool value)
	{
		Top()->m_enable_wireframe = value;
	}

	void Frame::FrameImpl::EnableTerrainRendering(bool value)
	{
		Top()->m_enable_terrain = value;
	}

	void Frame::FrameImpl::EnableLighting(bool value)
	{
		Top()->m_enable_lighting = value;
	}

	void Frame::FrameImpl::EnableTexturing(bool value)
	{
		Top()->m_enable_texture = value;
	}

	void Frame::FrameImpl::SetAmbientColor(float value)
	{
		Top()->m_ambient_color = value;
	}
	
	void Frame::FrameImpl::SetClipSpace(const Math::ClipSpace& value)
	{
		Top()->m_clip_space = value;
	}
	
	void Frame::FrameImpl::SetHeightMap(const Texture2D* value)
	{
		Top()->m_height_map = value;
	}

	void Frame::FrameImpl::SetLineWidth(float value)
	{
		Top()->m_line_width = value;
	}

	void Frame::FrameImpl::SetPointSize(float value)
	{
		Top()->m_point_size = value;
	}

	void Frame::FrameImpl::SetTextureMatrix(const Math::mat4& value)
	{
		Top()->m_texture_matrix = value;
	}
	
	void Frame::FrameImpl::SetLocalMatrix(const Math::mat4& value)
	{
		Top()->m_local = value;
	}

	void Frame::FrameImpl::SetSpecularFactor(float value)
	{
		Top()->m_specular_factor = value;
	}

	Frame::Frame()
		: impl(new FrameImpl)
	{}

	Frame::~Frame()
	{
		delete impl;
		impl = nullptr;
	}

	void Frame::BeginRendering()
	{
		impl->BeginRendering();
	}

	void Frame::Render(Renderable* value)
	{
		impl->Render(value);
	}

	void Frame::PushState()
	{
		impl->PushState();
	}

	void Frame::PopState()
	{
		impl->PopState();
	}

	void Frame::SetWorldMatrix(const Math::mat4& value)
	{
		impl->SetWorldMatrix(value);
	}

	void Frame::MultWorldMatrix(const Math::mat4& value)
	{
		impl->MultWorldMatrix(value);
	}

	void Frame::SetViewMatrix(const Math::mat4& value)
	{
		impl->SetViewMatrix(value);
	}

	void Frame::SetProjectionMatrix(const Math::mat4& value)
	{
		impl->SetProjectionMatrix(value);
	}

	void Frame::SetDiffuseColor(const Math::vec4& value)
	{
		impl->SetDiffuseColor(value);
	}

	void Frame::SetDiffuseMap0(const Texture2D* value)
	{
		impl->SetDiffuseMap0(value);
	}
	
	void Frame::SetDiffuseMap1(const Texture2D* value)
	{
		impl->SetDiffuseMap1(value);
	}
	
	void Frame::EnableDiffuseShading(bool value)
	{
		impl->EnableDiffuseShading(value);
	}

	void Frame::EnableSkinning(bool value)
	{
		impl->EnableSkinning(value);
	}

	void Frame::SetBoneMatrix(int bone_index, const Math::mat4& value)
	{
		impl->SetBoneMatrix(bone_index, value);
	}

	void Frame::SetSpecularColor(const Math::vec4& value)
	{
		impl->SetSpecularColor(value);
	}

	void Frame::SetSpecularMap(const Texture2D* value)
	{
		impl->SetSpecularMap(value);
	}

	void Frame::EnableSpecularShading(bool value)
	{
		impl->EnableSpecularShading(value);
	}

	void Frame::SetBumpMap(const Texture2D* value)
	{
		impl->SetBumpMap(value);
	}

	//void Frame::EnableBumpMapping(bool value)
	//{
	//	impl->EnableBumpMapping(value);
	//}

	void Frame::CastShadows(bool value)
	{
		impl->CastShadows(value);
	}

	void Frame::ReceiveShadow(bool value) 
	{
		impl->ReceiveShadow(value);
	}

	void Frame::EndRendering() 
	{
		impl->EndRendering();
	}

	const Math::mat4& Frame::GetWorldMatrix() const
	{
		return impl->GetWorldMatrix();
	}

	const Math::mat4& Frame::GetViewMatrix() const
	{
		return impl->GetViewMatrix();
	}

	const Math::mat4& Frame::GetProjectionMatrix() const
	{
		return impl->GetProjectionMatrix();
	}

	const Math::vec4& Frame::GetDiffuseColor() const
	{
		return impl->GetDiffuseColor();
	}

	const Texture2D* Frame::GetDiffuseMap0() const
	{
		return impl->GetDiffuseMap0();
	}

	const Texture2D* Frame::GetDiffuseMap1() const
	{ 
		return impl->GetDiffuseMap1();
	}
	
	const Math::mat4& Frame::GetBoneMatrix(int bone_index) const
	{
		return impl->GetBoneMatrix(bone_index);
	}

	const Math::vec4& Frame::GetSpecularColor() const
	{
		return impl->GetSpecularColor();
	}

	const Texture2D* Frame::GetSpecularMap() const
	{
		return impl->GetSpecularMap();
	}

	const Texture2D* Frame::GetBumpMap() const
	{
		return impl->GetBumpMap();
	}

	const Math::ClipSpace& Frame::GetClipSpace() const
	{
		return impl->GetClipSpace();
	}

	void Frame::EnableBlending(bool value)
	{
		impl->EnableBlending(value);
	}

	void Frame::EnableDepthTest(bool value)
	{
		impl->EnableDepthTest(value);
	}

	//void Frame::EnableSpecularShading(bool value)
	//{
	//	impl->EnableSpecularShading(value);
	//}

	void Frame::EnableBumpMapping(bool value)
	{
		impl->EnableBumpMapping(value);
	}

	//void Frame::EnableDiffuseShading(bool value)
	//{
	//	impl->EnableDiffuseShading(value);
	//}

	//void Frame::EnableSkinning(bool value)
	//{
	//	impl->EnableSkinning(value);
	//}

	void Frame::EnableWireframe(bool value)
	{
		impl->EnableWireframe(value);
	}

	void Frame::EnableTerrainRendering(bool value)
	{
		impl->EnableTerrainRendering(value);
	}

	void Frame::EnableLighting(bool value)
	{
		impl->EnableTerrainRendering(value);
	}

	void Frame::EnableTexturing(bool value)
	{
		impl->EnableTexturing(value);
	}

	void Frame::SetAmbientColor(float value)
	{
		impl->SetAmbientColor(value);
	}

	void Frame::SetClipSpace(const Math::ClipSpace& value)
	{
		impl->SetClipSpace(value);
	}

	void Frame::SetHeightMap(const Texture2D* value)
	{
		impl->SetHeightMap(value);
	}
	
	void Frame::SetLineWidth(float value)
	{
		impl->SetLineWidth(value);
	}

	void Frame::SetPointSize(float value)
	{
		impl->SetPointSize(value);
	}
	
	void Frame::SetTextureMatrix(const Math::mat4& value)
	{
		impl->SetTextureMatrix(value);
	}
	
	void Frame::SetLocalMatrix(const Math::mat4& value)
	{
		impl->SetLocalMatrix(value);
	}

	void Frame::SetSpecularFactor(float value)
	{
		impl->SetSpecularFactor(value);
	}
}