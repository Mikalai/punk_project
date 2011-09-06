#include "../../driver/video/opengl/driver.h"
#include "../../shaders/shader_manager.h"
#include "2d_text.h"
#include "../font_builder.h"


namespace Render
{
	namespace _2D
	{
		void Text::SetText(const char* text)
		{
			m_text = text;
			m_color[0] = 0;
			m_color[1] = m_color[2] = m_color[3] = 0;
			RenderTextToTexture();
		}

		Text::Text(float x, float y, int widthInSymbols, int heightInSymbols, int symbolSize) : m_widthInSymbols(widthInSymbols), m_heightInSymbols(heightInSymbols), m_symbolSize(symbolSize)
		{					
			m_x = x;
			m_y = y;
			m_width = m_widthInSymbols*m_symbolSize;
			m_height = m_heightInSymbols*m_symbolSize;
			widthInSymbols = 1;
			heightInSymbols = 1;
			float dx = 1.0f;
			float dy = 1.0f;

			::Driver::Video::CheckError();
			if(!(m_program = Shaders::g_ShaderManager.GetProgram("textured_2d")))
				throw System::Exception("solid_color_2d program not found");

			BindShaderData();

//			m_vertexCount = 4;//(m_widthInSymbols+1)*(m_heightInSymbols+1);
	//		m_indexCount = 4;//(m_widthInSymbols+1)*2*m_heightInSymbols+2*(m_heightInSymbols-1);
			
			Vertex v[4] = {{0,0,0,1},{1,0,1,1},{1,1,1,0},{0,1,0,0}};
			unsigned short index[] = {0,3,2,1};

			m_vertexCount = 4;
			m_indexCount = 4;

			Driver::Video::CheckError("");

			if (Driver::g_openGLDriver.OpenGLVersion >= 300)
			{
				glGenVertexArrays(1, &m_vao);
				glBindVertexArray(m_vao);
			}

			::Driver::Video::CheckError();

			glGenBuffers(1, &m_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(Vertex), v, GL_STATIC_DRAW);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);

			::Driver::Video::CheckError();

			glGenBuffers(1, &m_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(unsigned short), index, GL_STATIC_DRAW);
			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indexCount*sizeof(unsigned short), m_index);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			::Driver::Video::CheckError();

			glEnableVertexAttribArray(m_vertexAttrib);
			glEnableVertexAttribArray(m_textureVertexAttrib);
			glVertexAttribPointer(m_vertexAttrib, 2, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)Vertex::PositionOffset);
			glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TextureOffset);
			

			if (Driver::g_openGLDriver.OpenGLVersion >= 300)
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
			::Driver::Video::CheckError();

			m_texture.Create(m_width, m_height, ImageLoader::IMAGE_FORMAT_RED, 1, 0);
			RenderTextToTexture();
			
		}

		void Text::RenderTextToTexture()
		{
			int x = 0;
			int y = m_texture.GetHeight() - 25;
			Render::FontBuilder::SetCharSize(5,6);
			for (std::string::iterator it = m_text.begin(); it != m_text.end(); ++it)
			{ 
				int width;
				int height;
				int x_offset;
				int y_offset;
				int x_advance;
				int y_advance;
				unsigned char* buffer;
				FontBuilder::RenderChar(*it, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
				m_texture.CopyFromCPU(x + x_offset, m_texture.GetHeight() - (y + y_offset), width, height, ImageLoader::IMAGE_FORMAT_RED, buffer);
				x += x_advance;				
			}
		}


		void Text::Render()
		{
			if (Driver::g_openGLDriver.OpenGLVersion >= 300)
				glBindVertexArray(m_vao);
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			}

			if (!System::g_desktop)
				throw System::Exception("FATAL ERROR: g_desktop not set");

			Math::mat4 worldViewProj = Math::mat4::CreateScaling(m_width, m_height, 1)*Math::mat4::CreateTranslate(m_x, m_y, 0)*Math::mat4::CreateOrthographicProjection(0, System::g_desktop->GetWidth(), System::g_desktop->GetHeight(), 0, -1.0f, 1.0f);

			int passCount = m_program->GetPassCount();
			for (int i = 0; i < passCount; i++)
			{
				m_program->Bind(i);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				//glBlendEquation(GL_FUNC_ADD);
				Driver::Video::CheckError("-1");
				
				m_program->SetUniformMatrix4f(m_worldViewProjUniform, worldViewProj.m);
				m_program->SetUniformVector4f(m_diffuseColorUniform, m_color);
				m_program->SetTexture(m_baseMapUniform, 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_texture);
				
				Driver::Video::CheckError("0");

				//glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
				if (Driver::g_openGLDriver.OpenGLVersion >= 300)
				{
				}
				else
				{
					/*   glEnableVertexAttribArray(m_vertexAttrib);
					glEnableVertexAttribArray(m_normalAttrib);
					if (m_textureVertexAttrib != -1) {
					glEnableVertexAttribArray(m_textureVertexAttrib);
					glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE,
					sizeof(Vertex), (void*)Vertex::TextureOffset);
					}
					glEnableVertexAttribArray(m_binormalAttrib);
					glEnableVertexAttribArray(m_tangentAttrib);
					glVertexAttribPointer(m_vertexAttrib, 3, GL_FLOAT, GL_FALSE,
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
			if (Driver::g_openGLDriver.OpenGLVersion >= 300)
				glBindVertexArray(0);
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			Driver::Video::CheckError("6");
			m_program->Unbind();
		}

		void Text::BindShaderData()
		{
			m_vertexAttrib = m_program->GetAttribLocation("rm_Vertex");
			m_textureVertexAttrib = m_program->GetAttribLocation("rm_Texcoord");
			m_worldViewProjUniform = m_program->GetUniformLocation("uWorldViewProj");
			m_diffuseColorUniform = m_program->GetUniformLocation("uDiffuseColor");
			m_baseMapUniform = m_program->GetUniformLocation("uBaseMap");
		}
	}
}