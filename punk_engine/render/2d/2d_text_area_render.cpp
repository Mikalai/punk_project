#include "2d_text_area_render.h"
#include "../font_builder.h"
#include "../../driver/video/opengl/texture2d_object.h"
#include "../../shaders/shader_manager.h"

namespace Render
{
	TextAreaRender* g_render;

	TextAreaRender* TextAreaRender::GetRender()
	{
		if (g_render)
			return g_render;
		g_render = new TextAreaRender();
		return g_render;
	}

	std::queue<TextAreaRender::Parameters*> TextAreaRender::Parameters::parametersPool;

    void TextAreaRender::Parameters::Release()
    {
        this->parametersPool.push(this);
    }

	void TextAreaRender::Parameters::Set(float x, float y, float width, float height, float* color, Driver::Texture2D* texture)
	{
		m_x = x; m_y = y; m_width = width; m_height = height; m_texture = texture;
		m_color[0] = color[0]; m_color[1] = color[1]; m_color[2] = color[2]; m_color[3] = color[3];
	}

    TextAreaRender::Parameters* TextAreaRender::Parameters::Create()
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
/*
	void TextAreaRender::SetText(const char* text)
	{
		m_text = text;
		m_color[0] = 1;
		m_color[1] = m_color[2] = m_color[3] = 1;
		RenderTextToTexture();
	}

	void TextAreaRender::SetTextSize(int size)
	{
		m_fontSize = size;
		FontBuilder::SetCharSize(size, size);
		RenderTextToTexture();
	}*/

	TextAreaRender::TextAreaRender()
	{					
		float dx = 1.0f;
		float dy = 1.0f;

		::Driver::CheckError();
		if(!(m_program = Shaders::g_ShaderManager.GetProgram(L"textured_2d")))
			throw System::Exception(L"solid_color_2d program not found" + LOG_LOCATION_STRING);

		BindShaderData();

		//			m_vertexCount = 4;//(m_widthInSymbols+1)*(m_heightInSymbols+1);
		//		m_indexCount = 4;//(m_widthInSymbols+1)*2*m_heightInSymbols+2*(m_heightInSymbols-1);

		Vertex v[4] = {{0,0,0,1},{1,0,1,1},{1,1,1,0},{0,1,0,0}};
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
		glEnableVertexAttribArray(m_textureVertexAttrib);
		glVertexAttribPointer(m_vertex_attribute, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)Vertex::PositionOffset);
		glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TextureOffset);


		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
		{
			glBindVertexArray(0);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		//	delete[] v;
		//delete[] index;
		::Driver::CheckError();
		
		/*RenderTextToTexture();*/

	}

	void TextAreaRender::Render(void* parameters)
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

		Math::mat4 projViewWorld = Math::mat4::CreateScaling(p->m_width, p->m_height, 1.0f)*Math::mat4::CreateTranslate(p->m_x, p->m_y, 0.0f)*Math::mat4::CreateOrthographicProjection(0.0f, (float)System::g_desktop->GetWidth(), (float)System::g_desktop->GetHeight(), 0.0f, -1.0f, 1.0f);

		int passCount = m_program->GetPassCount();
		for (int i = 0; i < passCount; i++)
		{
			m_program->Bind(i);

			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glBlendEquation(GL_FUNC_ADD);
			Driver::CheckError(L"-1");

			m_program->SetUniformMatrix4f(m_proj_view_world_uniform, projViewWorld);
			m_program->SetUniformVector4f(m_diffuse_color_uniform, p->m_color);
			m_program->SetTexture(m_baseMapUniform, 0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, p->m_texture->GetID());

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

			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);


		}
		if (Driver::Video::GetDriver()->OpenGLVersion >= 300)
			glBindVertexArray(0);
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		Driver::CheckError(L"6");
		m_program->Unbind();
		
		p->Release();
	}

	void TextAreaRender::BindShaderData()
	{
		m_vertex_attribute = m_program->GetAttribLocation("rm_Vertex");
		m_textureVertexAttrib = m_program->GetAttribLocation("rm_Texcoord");
		m_proj_view_world_uniform = m_program->GetUniformLocation("uProjViewWorld");
		m_diffuse_color_uniform = m_program->GetUniformLocation("uDiffuseColor");
		m_baseMapUniform = m_program->GetUniformLocation("uBaseMap");
	}
}