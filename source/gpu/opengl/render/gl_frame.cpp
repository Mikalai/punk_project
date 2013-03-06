#include "../../common/gpu_state.h"
#include "../../../system/state_manager.h"
#include "gl_batch.h"
#include "gl_frame.h"
#include "../driver/gl_driver.h"

namespace GPU
{
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
	}

	void Frame::FrameImpl::SetVideoDriver(VideoDriver* driver)
	{
		m_driver = driver;
	}

	const Math::mat4& Frame::FrameImpl::GetWorldMatrix()
	{
		return Top()->m_world;
	}

	const Math::mat4& Frame::FrameImpl::GetViewMatrix()
	{
		return Top()->m_view;
	}

	const Math::mat4& Frame::FrameImpl::GetProjectionMatrix()
	{
		return Top()->m_projection;
	}

	const Math::vec4& Frame::FrameImpl::GetDiffuseColor()
	{
		return Top()->m_diffuse_color;
	}

	const Texture2D* Frame::FrameImpl::GetDiffuseMap0()
	{
		return Top()->m_diffuse_map_0;
	}

	const Texture2D* Frame::FrameImpl::GetDiffuseMap1()
	{
		return Top()->m_diffuse_map_1;
	}

	const Math::mat4& Frame::FrameImpl::GetBoneMatrix(int bone_index)
	{
		return Top()->m_bone_matrix[bone_index];
	}

	const Math::vec4& Frame::FrameImpl::GetSpecularColor()
	{
		return Top()->m_specular_color;
	}

	const Texture2D* Frame::FrameImpl::GetSpecularMap()
	{
		return Top()->m_specular_map;
	}

	const Texture2D* Frame::FrameImpl::GetBumpMap()
	{
		return Top()->m_normal_map;
	}

	Frame::Frame()
		: impl(new FrameImpl)
	{}

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

	void Frame::EnableBumpMapping(bool value)
	{
		impl->EnableBumpMapping(value);
	}

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

	const Math::mat4& Frame::GetWorldMatrix()
	{
		return impl->GetWorldMatrix();
	}

	const Math::mat4& Frame::GetViewMatrix()
	{
		return impl->GetViewMatrix();
	}

	const Math::mat4& Frame::GetProjectionMatrix()
	{
		return impl->GetProjectionMatrix();
	}

	const Math::vec4& Frame::GetDiffuseColor()
	{
		return impl->GetDiffuseColor();
	}

	const Texture2D* Frame::GetDiffuseMap0()
	{
		return impl->GetDiffuseMap0();
	}

	const Texture2D* Frame::GetDiffuseMap1()
	{
		return impl->GetDiffuseMap1();
	}
	
	const Math::mat4& Frame::GetBoneMatrix(int bone_index)
	{
		return impl->GetBoneMatrix(bone_index);
	}

	const Math::vec4& Frame::GetSpecularColor()
	{
		return impl->GetSpecularColor();
	}

	const Texture2D* Frame::GetSpecularMap()
	{
		return impl->GetSpecularMap();
	}

	const Texture2D* Frame::GetBumpMap()
	{
		return impl->GetBumpMap();
	}
}