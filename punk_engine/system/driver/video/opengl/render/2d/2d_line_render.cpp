#include "2d_line_render.h"
#include "../../driver/video/driver.h"
#include "../../shaders/shader_manager.h"

namespace Render
{
	LineRender* g_render = 0;

	LineRender* LineRender::GetRender()
	{
		if (g_render)
			return g_render;
		g_render = new LineRender();
		return g_render;
	}

	std::queue<LineRender::Parameters*> LineRender::Parameters::parametersPool;

    void LineRender::Parameters::Release()
    {
        this->parametersPool.push(this);
    }

	void LineRender::Parameters::Set(float x1, float y1, float x2, float y2, float* color)
	{
		m_p1[0] = x1;
		m_p1[1] = y1;
		m_p2[0] = x2;
		m_p2[1] = y2;
		m_back_color[0] = color[0]; m_back_color[1] = color[1]; m_back_color[2] = color[2]; m_back_color[3] = color[3];
	}

    LineRender::Parameters* LineRender::Parameters::Create()
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

	LineRender::LineRender()
	{
		::Driver::CheckError();
		if(!(m_program = Shaders::g_ShaderManager.GetProgram(L"line_2d")))
			throw System::Exception(L"solid_color_2d program not found" + LOG_LOCATION_STRING);

		BindShaderData();

		Vertex v[2] = {{0,0},{1,0}};
		unsigned short index[] = {0,1};

		m_vertexCount = 2;
		m_indexCount = 2;

		Driver::CheckError(L"");

		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
		{
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
		}

		::Driver::CheckError();

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(Vertex), v, GL_STATIC_DRAW);
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

	void LineRender::BindShaderData()
	{
		m_vertex_attribute = m_program->GetAttribLocation("rm_Vertex");
		m_diffuse_color_uniform = m_program->GetUniformLocation("uDiffuseColor");
		m_p1Uniform = m_program->GetUniformLocation("uP1");
		m_p2Uniform = m_program->GetUniformLocation("uP2");
		m_widthUniform = m_program->GetUniformLocation("uWidth");
		m_heightUniform = m_program->GetUniformLocation("uHeight");
	}

	void LineRender::Render(void* parameters)
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

		float width = (float)System::g_desktop->GetWidth();
		float height = (float)System::g_desktop->GetHeight();

		int passCount = m_program->GetPassCount();
		for (int i = 0; i < passCount; i++)
		{
			m_program->Bind(i);
			Driver::CheckError(L"-1");
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_program->SetUniformVector4f(m_diffuse_color_uniform, p->m_back_color);
			m_program->SetUniformVector2f(m_p1Uniform, p->m_p1);
			m_program->SetUniformVector2f(m_p2Uniform, p->m_p2);
			m_program->SetUniformFloat(m_widthUniform, width);
			m_program->SetUniformFloat(m_heightUniform, height);

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
			glDrawElements(GL_LINES, m_indexCount, GL_UNSIGNED_SHORT, 0);


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

	LineRender::~LineRender()	
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteBuffers(1, &m_indexBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}
}