#include "2d_quad_render.h"
#include "../../driver/video/opengl/driver.h"
#include "../../shaders/shader_manager.h"

namespace Render
{
	QuadRender* g_render = 0;

	QuadRender* QuadRender::GetRender()
	{
		if (g_render)
			return g_render;
		g_render = new QuadRender();
		return g_render;
	}

	std::queue<QuadRender::Parameters*> QuadRender::Parameters::parametersPool;

    void QuadRender::Parameters::Release()
    {
        this->parametersPool.push(this);
    }

    QuadRender::Parameters* QuadRender::Parameters::Create()
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

	void QuadRender::Parameters::Set(float x, float y, float width, float height, float* color)
	{
		m_x = x; m_y = y; m_width = width; m_height = height; 
		m_color[0] = color[0]; m_color[1] = color[1], m_color[2] = color[2]; m_color[3] = color[3];
	}

	QuadRender::QuadRender()
	{
		::Driver::CheckError();
		if(!(m_program = Shaders::g_ShaderManager.GetProgram(L"solid_color_2d")))
			throw System::Exception(L"solid_color_2d program not found" + LOG_LOCATION_STRING);

		BindShaderData();

		Vertex v[4] = {{0,0},{1,0},{1,1},{0,1}};
		unsigned short index[] = {0,3,2,1};

		m_vertexCount = 4;
		m_indexCount = 4;

		Driver::CheckError(L"");

		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
		{
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
		}

		::Driver::CheckError();

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vertex), v, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		::Driver::CheckError();

		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(unsigned short), index, GL_STATIC_DRAW);
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indexCount*sizeof(unsigned short), m_index);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		::Driver::CheckError();

		glEnableVertexAttribArray(m_vertex_attribute);
		glVertexAttribPointer(m_vertex_attribute, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)Vertex::PositionOffset);

		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
		{
			glBindVertexArray(0);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		::Driver::CheckError();
	}

	void QuadRender::BindShaderData()
	{
		m_vertex_attribute = m_program->GetAttribLocation("rm_Vertex");
		m_proj_view_world_uniform = m_program->GetUniformLocation("uProjViewWorld");
		m_diffuse_color_uniform = m_program->GetUniformLocation("uDiffuseColor");
		m_radiusUniform = m_program->GetUniformLocation("uRadius");

	}

	void QuadRender::Render(void* parameters)
	{		
		Parameters* p = static_cast<Parameters*>(parameters);

		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
			glBindVertexArray(m_vao);
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		}

		if (!System::g_desktop)
			throw System::Exception(L"FATAL ERROR: g_desktop not set" + LOG_LOCATION_STRING);

		Math::mat4 projViewWorld = Math::mat4::CreateOrthographicProjection(0.0f, (float)System::g_desktop->GetWidth(), (float)System::g_desktop->GetHeight(), 0.0f, -1.0f, 1.0f)
			*Math::mat4::CreateTranslate(p->m_x, p->m_y, 0.0f)*Math::mat4::CreateScaling(p->m_width, p->m_height, 1.0f);

		int passCount = m_program->GetPassCount();
		for (int i = 0; i < passCount; i++)
		{
			m_program->Bind(i);
			Driver::CheckError(L"-1");
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_program->SetUniformMatrix4f(m_proj_view_world_uniform, projViewWorld);
			m_program->SetUniformVector4f(m_diffuse_color_uniform, p->m_color);
			m_program->SetUniformFloat(m_radiusUniform, 5.0f);

			Driver::CheckError(L"0");

			//glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
			if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
			{
			}
			else
			{
				/*   glEnableVertexAttribArray(m_vertex_attribute);
				glEnableVertexAttribArray(m_normalAttrib);
				if (m_textureVertexAttrib != -1) {
				glEnableVertexAttribArray(m_textureVertexAttrib);
				glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::TextureOffset);
				}
				glEnableVertexAttribArray(m_binormalAttrib);
				glEnableVertexAttribArray(m_tangentAttrib);
				glVertexAttribPointer(m_vertex_attribute, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::PositionOffset);
				glVertexAttribPointer(m_normalAttrib, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::NormalOffset);
				glVertexAttribPointer(m_binormalAttrib, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::BinormalOffset);
				glVertexAttribPointer(m_tangentAttrib, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::TangentOffset);*/
			}
			glDrawElements(GL_TRIANGLE_FAN, m_indexCount, GL_UNSIGNED_SHORT, 0);
		}

		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
			glBindVertexArray(0);
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		Driver::CheckError(L"6");
		m_program->Unbind();

		p->Release();
	}

	QuadRender::~QuadRender()
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteBuffers(1, &m_indexBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}
}