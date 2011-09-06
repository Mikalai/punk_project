#include "3d_line_render.h"
#include "../shaders/shader_manager.h"
#include "../driver/video/opengl/shader_program.h"

namespace Render
{
	LineRender3D* g_render = 0;

	LineRender3D* LineRender3D::GetRender()
	{
		if (g_render)
			return g_render;
		g_render = new LineRender3D();
		return g_render;
	}

	std::queue<LineRender3D::Parameters*> LineRender3D::Parameters::parametersPool;

    void LineRender3D::Parameters::Release()
    {
        this->parametersPool.push(this);
    }

    LineRender3D::Parameters* LineRender3D::Parameters::Create()
    {
        if (parametersPool.empty())
        {
            Parameters* event = new Parameters();
            return event;
        }
        else
        {
            Parameters* event = parametersPool.front();
            parametersPool.pop();
            return event;
        }
    }

	void LineRender3D::Parameters::Set(const VertexArrayObject* vao, 
				const Math::mat4& world_transform, 
				const Math::mat4& view_transform,
				const Math::mat4& projection_transform,
				Math::vec4& color)
	{
		m_vertex_array_object = vao;
		m_color = color;
		m_world_transform = world_transform;
		m_view_transform = view_transform;
		m_projection_transform = projection_transform;
	}

	LineRender3D::LineRender3D()
	{
		::Driver::CheckError();
		if(!(m_shader_program = Shaders::g_ShaderManager.GetProgram(L"solid_color_3d")))
			throw System::Exception(L"solid_color_3d program not found" + LOG_LOCATION_STRING);

		BindShaderData();

	}

	void LineRender3D::BindShaderData()
	{
		m_vertexAttrib = m_shader_program->GetAttribLocation("rm_Vertex");
		m_worldViewProjUniform = m_shader_program->GetUniformLocation("uWorldViewProj");
		m_diffuseColorUniform = m_shader_program->GetUniformLocation("uDiffuseColor");
	}

	void LineRender3D::Render(void* parameters)
	{		
		Parameters* p = static_cast<Parameters*>(parameters);
		
		Math::mat4 worldViewProj = p->m_world_transform*p->m_view_transform*p->m_projection_transform;
			
		p->m_vertex_array_object->Bind();
		
		int passCount = m_shader_program->GetPassCount();
		for (int i = 0; i < passCount; i++)
		{
			m_shader_program->Bind(i);			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader_program->SetUniformMatrix4f(m_worldViewProjUniform, worldViewProj);
			m_shader_program->SetUniformVector4f(m_diffuseColorUniform, p->m_color);
			//glDrawRangeElements(GL_TRIANGLES, 0,  p->m_vertex_array_object.GetIndexCount() / 3, GL_UNSIGNED_SHORT, 0);
			glDrawElements(GL_TRIANGLES, p->m_vertex_array_object->GetIndexCount(), GL_UNSIGNED_SHORT, 0);

		}		

		m_shader_program->Unbind();

		p->m_vertex_array_object->Unbind();

		p->Release();
	}

	LineRender3D::~LineRender3D()
	{
	}
}