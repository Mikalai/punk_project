#include "../../common/frame.h"
#include "../../common/gpu_state.h"
#include "../../../system/state_manager.h"
#include "gl_batch.h"

namespace GPU
{
	struct Frame::FrameImpl
	{
		std::stack<CoreState*> m_state;
		std::vector<OpenGL::Batch*> m_batches;

		void BeginRendering()
		{
			m_state.push(new CoreState);
		}

		void Render(Renderable* value)
		{
			OpenGL::Batch* batch = new OpenGL::Batch;
			batch->m_renderable = value;
			batch->m_state = m_state.top()->Clone();
			m_batches.push_back(batch);
		}

		void PushState()
		{
			m_state.push(m_state.top()->Clone());
		}

		void PopState()
		{
			delete m_state.top();
			m_state.pop();
		}

		CoreState* Top()
		{
			return m_state.top();
		}

		void SetWorldMatrix(const Math::mat4& value)
		{
			Top()->m_world = value;
		}
			
		void SetViewMatrix(const Math::mat4& value)
		{
			Top()->m_view = value;
		}

		void SetProjectionMatrix(const Math::mat4& value)
		{
			Top()->m_projection = value;
		}

		void SetDiffuseColor(const Math::vec4& value)
		{
			Top()->m_diffuse_color = value;
		}

		void SetDiffuseMap(const Texture2D* value)
		{
			Top()->m_diffuse_map = value;
		}

		void EnableDiffuseShading(bool value)
		{
			Top()->m_enable_diffuse_shading = value;
		}

		void EnableSkinning(bool value)
		{
			Top()->m_enable_skinning = value;
		}

		void SetBoneMatrix(int bone_index, const Math::mat4& value)
		{
			Top()->m_bone_matrix[bone_index] = value;
		}

		void SetSpecularColor(const Math::vec4& value)
		{
			Top()->m_specular_color = value;
		}

		void SetSpecularMap(const Texture2D* value)
		{
			Top()->m_specular_map = value;
		}

		void EnableSpecularShading(bool value)
		{
			Top()->m_enable_specular_shading = value;
		}

		void SetBumpMap(const Texture2D* value)
		{
			Top()->m_normal_map = value;
		}

		void EnableBumpMapping(bool value)
		{
			Top()->m_enable_bump_mapping = value;
		}

		void CastShadows(bool value)
		{
			Top()->m_cast_shadows = value;
		}

		void ReceiveShadow(bool value)
		{
			Top()->m_receive_shadows = value;
		}

		void EndRendering()
		{
			//	array of batches should be submitted to the actual rendering
		}
	};


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

	void Frame::SetDiffuseMap(const Texture2D* value)
	{
		impl->SetDiffuseMap(value);
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
}