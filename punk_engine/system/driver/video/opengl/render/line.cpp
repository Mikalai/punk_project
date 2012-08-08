#include "../../../../environment.h"
#include "line.h"

namespace OpenGL
{
	void Line::Init()
	{
		m_vertex_shader.reset(new Shader(Shader::SHADER_VERTEX));
		m_vertex_shader->CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"line_330.vert");
		m_fragment_shader.reset(new Shader(Shader::SHADER_FRAGMENT));
		m_fragment_shader->CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"line_330.frag");

		m_render.reset(new RenderContext());
		m_render->SetVertexShader(m_vertex_shader.get());
		m_render->SetFragmentShader(m_fragment_shader.get());		
		m_render->Init();

		m_proj_view_world_uniform = m_render->GetUniformLocation("uProjViewWorld");
		m_start_uniform = m_render->GetUniformLocation("uStart");
		m_end_uniform = m_render->GetUniformLocation("uEnd");
		m_color_uniform = m_render->GetUniformLocation("uDiffuseColor");

		InitVAO();
	}

	void Line::InitVAO()
	{
		struct Vertex { Math::vec4 value; };
		std::vector<Vertex> m_vb(2);
		m_vb[0].value.Set(0, 0, 0, 0);
		m_vb[1].value.Set(1, 0, 0, 0);
		std::vector<unsigned> m_ib(2);
		m_ib[0] = 0;
		m_ib[1] = 1;

		m_vao.reset(new VertexArrayObject);
		m_vao->SetVertexBuffer(&m_vb[0], m_vb.size() * sizeof(Vertex), sizeof(Vertex));
		m_vao->SetIndexBuffer(&m_ib[0], m_ib.size() * sizeof(unsigned));		
		m_vao->Cook(VERTEX_POSITION, GL_LINES);
		m_vao->Init();
	}
	
	void Line::Clear()
	{
	}

	void Line::SetLocalTransform(const Math::mat4& value)
	{
		m_local = value;
	}
	
	void Line::SetViewTranform(const Math::mat4& value)
	{
		m_view = value;
	}

	void Line::SetProjectionTransform(const Math::mat4& value)
	{
		m_proj = value;
	}

	void Line::SetColor(float r, float g, float b, float a)
	{
		m_color.Set(r, g, b, a);
	}

	void Line::SetColor(const Math::vec4& color)
	{
		m_color = color;
	}

	void Line::Draw(const Math::vec3& p1, const Math::vec3& p2)
	{		
		m_render->EnableDepthTest(false);
		m_render->Begin();
		m_render->SetUniformVector3f(m_start_uniform, p1);
		m_render->SetUniformVector3f(m_end_uniform, p2);
		m_render->SetUniformMatrix4f(m_proj_view_world_uniform, &(m_proj*m_view*m_local)[0]);
		m_render->SetUniformVector4f(m_color_uniform, m_color);		
		m_vao->Bind(VERTEX_POSITION);
		m_vao->Render();
		m_vao->Unbind();
		m_render->End();
		m_render->EnableDepthTest(true);
	}

}