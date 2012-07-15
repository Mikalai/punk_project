#include "../system/driver/video/driver.h"

#include "simple_renderpipeline.h"

using namespace OpenGL;

namespace Render
{
	SimpleRender::SimpleRender()
	{
		m_bump_mapping.reset(new RenderContextBumpMapping);
		m_texture_context.reset(new TextureContext);
	}

	void SimpleRender::AddStaticRenderable(StaticRenderable r)
	{
		m_queue.push_back(r);
	}

	void SimpleRender::SetProjectionMatrix(const Math::mat4& m)
	{
		m_proj_matrix = m;
	}

	void SimpleRender::SetViewMatrix(const Math::mat4& m)
	{
		m_view_matrix = m;
	}

	void SimpleRender::Process()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto it = m_queue.begin(); it != m_queue.end(); ++it)
		{
			m_bump_mapping->SetWorldMatrix(it->GetLocalTransform());
			m_bump_mapping->SetViewMatrix(m_view_matrix);
			m_bump_mapping->SetProjectionMatrix(m_proj_matrix);
			m_bump_mapping->SetAmbientColor(Math::vec4(0,0,0,0));
			m_bump_mapping->SetSpecularColor(Math::vec4(1,1,1,1));
			m_bump_mapping->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_bump_mapping->SetSpecularPower(16);
			m_bump_mapping->SetLightPosition(Math::vec3(10, 1, 10));
			m_bump_mapping->Begin();		
			m_texture_context->SetTexture0(it->GetDiffuseMap());
			m_texture_context->SetTexture1(it->GetNormalMap());
			m_texture_context->Bind();
			it->GetVAO()->Bind(m_bump_mapping->GetSupportedVertexAttributes());
			it->GetVAO()->Render();		
			it->GetVAO()->Unbind();
			m_texture_context->Unbind();
			m_bump_mapping->End();
		}		

		m_queue.clear();
	}
}