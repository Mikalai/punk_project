#include "per_vertex_render.h"
#include "../shaders/shader_manager.h"
#include "../driver/video/opengl/shader_program.h"

namespace Render
{
	PerVertexRender* g_render = 0;

	PerVertexRender* PerVertexRender::GetRender()
	{
		if (g_render)
			return g_render;
		g_render = new PerVertexRender();
		return g_render;
	}

	std::queue<PerVertexRender::Parameters*> PerVertexRender::Parameters::parametersPool;

    void PerVertexRender::Parameters::Release()
    {
        this->parametersPool.push(this);
    }

    PerVertexRender::Parameters* PerVertexRender::Parameters::Create()
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

	void PerVertexRender::Parameters::Set(const VertexArrayObject* vao, 
				const Math::mat4& world_transform, 
				const Math::mat4& view_transform,
				const Math::mat4& projection_transform,
				const Math::vec4& color,
				const Math::vec3& light_direction,
				const Math::vec3& light_positon)
	{
		m_vertex_array_object = vao;
		m_color = color;
		m_world_transform = world_transform;
		m_view_transform = view_transform;
		m_projection_transform = projection_transform;
		m_light_position = light_positon;
		m_light_direction = light_direction;
	}

	PerVertexRender::PerVertexRender()
	{
		::Driver::CheckError();
		if(!(m_shader_program = Shaders::g_ShaderManager.GetProgram(L"per_vertex_lighting")))
			throw System::Exception(L"per_vertex_lighting program not found" + LOG_LOCATION_STRING);

		BindShaderData();

	}

	void PerVertexRender::BindShaderData()
	{
		m_vertex_attribute = m_shader_program->GetAttribLocation("rm_Vertex");
		m_normalsAttrib = m_shader_program->GetAttribLocation("rm_Normal");
		m_proj_view_world_uniform = m_shader_program->GetUniformLocation("uProjViewWorld");
		m_diffuse_color_uniform = m_shader_program->GetUniformLocation("uDiffuseColor");
		m_normalTransformUniform = m_shader_program->GetUniformLocation("uNormalTransform");
		m_proj_view_world_uniform = m_shader_program->GetUniformLocation("uProjViewWorld");
		m_lightDirectionUniform = m_shader_program->GetUniformLocation("uLightDirection");
		m_lightPositionUniform = m_shader_program->GetUniformLocation("uLightPosition");
		m_viewUniform = m_shader_program->GetUniformLocation("uView");
	}

	void PerVertexRender::Render(void* parameters)
	{		
		Parameters* p = static_cast<Parameters*>(parameters);
		
		Math::mat4 projViewWorld = p->m_projection_transform*p->m_view_transform*p->m_world_transform;
		Math::mat3 normalTransform = (p->m_view_transform*p->m_world_transform).RotationPart();

		p->m_vertex_array_object->Bind();

		int passCount = m_shader_program->GetPassCount();
		
		for (int i = 0; i < passCount; i++)
		{
			m_shader_program->Bind(i);			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader_program->SetUniformMatrix4f(m_proj_view_world_uniform, projViewWorld);
			m_shader_program->SetUniformMatrix3f(m_viewUniform, p->m_view_transform.RotationPart());
			m_shader_program->SetUniformMatrix3f(m_normalTransformUniform, normalTransform);
			m_shader_program->SetUniformVector4f(m_diffuse_color_uniform, p->m_color);
			m_shader_program->SetUniformVector3f(m_lightPositionUniform, p->m_light_position);
			m_shader_program->SetUniformVector3f(m_lightDirectionUniform, p->m_light_direction);

			//glDrawRangeElements(GL_TRIANGLES, 0,  p->m_vertex_array_object.GetIndexCount() / 3, GL_UNSIGNED_SHORT, 0);
			glDrawElements(GL_TRIANGLES, p->m_vertex_array_object->GetIndexCount(), GL_UNSIGNED_SHORT, 0);			
		}		
		
		
		m_shader_program->Unbind();
	
		p->m_vertex_array_object->Unbind();

		p->Release();
	}

	PerVertexRender::~PerVertexRender()
	{
	}
}