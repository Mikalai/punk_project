#include "text_surface.h"
#include "../../../utility/fonts/font_builder.h"

namespace GPU
{
	namespace OpenGL
	{
		TextSurface::TextSurface()
		{
			m_texture.Reset(new Texture2D);		
			m_halignment = TextHorizontalAlignment::HORIZONTAL_LEFT;
			m_valignment = TextVerticalAlignment::VERTICAL_TOP;
			m_font = L"times.ttf";
			m_font_size = 14;
			m_auto_wrap = false;
		}

		void TextSurface::SetSize(int width, int height)
		{
			m_texture->Create(width, height, ImageModule::IMAGE_FORMAT_RED, 0, false);
		}

		int TextSurface::CalculateTextXOffset(const System::string& text)
		{
			int start_x;
			if (TextHorizontalAlignment::HORIZONTAL_LEFT == m_halignment)
				start_x = 0;
			else if (TextHorizontalAlignment::HORIZONTAL_CENTER == m_halignment)
			{
				int length = Utility::FontBuilder::Instance()->CalculateLength(text.Data());
				if (length >= m_texture->GetWidth())
					start_x = 0;
				else
					start_x = (m_texture->GetWidth() - length) / 2;
			}
			else if (TextHorizontalAlignment::HORIZONTAL_RIGHT == m_halignment)
			{
				int length = Utility::FontBuilder::Instance()->CalculateLength(text.Data());
				if (length >= m_texture->GetWidth())
					start_x = 0;
				else
					start_x = m_texture->GetWidth() - length;
			}
			return start_x;
		}

		int TextSurface::CalculateTextYOffset(const System::string& text)
		{
			const wchar_t* cur = text.Data();		
			int length = Utility::FontBuilder::Instance()->CalculateLength(cur);
			if (length == 0)
				return 1;		
			int max_offset = Utility::FontBuilder::Instance()->GetMaxOffset(text);
			int min_offset = Utility::FontBuilder::Instance()->GetMinOffset(text);
			int max_height = max_offset - min_offset;
			int max_lines = m_texture->GetHeight() / max_height;
			int req_lines = length / m_texture->GetWidth();
			int start_y = 0;
			if (TextVerticalAlignment::VERTICAL_BOTTOM == m_valignment)
			{
				start_y = 0;
			}
			else if (TextVerticalAlignment::VERTICAL_CENTER == m_valignment)
			{
				start_y = m_texture->GetHeight() / 2 + req_lines*max_height / 2;
			}
			else if (TextVerticalAlignment::VERTICAL_TOP == m_valignment)
			{
				start_y = max_offset;
			}
			return start_y;
		}

		bool TextSurface::RenderTextToTexture()
		{
			if (m_text.Length() == 0)
				return (m_texture->Fill(0), true);

			int start_x, start_y;
			int x = start_x = CalculateTextXOffset(m_text);
			int y = start_y = CalculateTextYOffset(m_text);
			m_texture->Fill(0);
			Utility::FontBuilder::Instance()->SetCurrentFace(m_font);
			Utility::FontBuilder::Instance()->SetCharSize(m_font_size, m_font_size);
			for (const wchar_t* a = m_text.Data(); *a; a++)
			{ 
				int width;
				int height;
				int x_offset;
				int y_offset;
				int x_advance;
				int y_advance;
				unsigned char* buffer;
				Utility::FontBuilder::Instance()->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
				if (x_offset < 0 && x == 0)
					x += -x_offset;
				if (x + x_offset + width >= m_texture->GetWidth())
				{
					y -= Utility::FontBuilder::Instance()->GetHeight(L'M');
					x = CalculateTextXOffset(a);
					if (y < 0)
						return true;
				}							
				m_texture->CopyFromCPU(x + x_offset, y - y_offset, width, height, buffer);			
				x += x_advance;				
			}/**/
			return true;
		}

		void TextSurface::SetFont(const System::string& font)
		{
			m_font = font;
			RenderTextToTexture();
		}

		void TextSurface::SetTextSize(int size)
		{
			m_font_size = size;
			RenderTextToTexture();
		}

		bool TextSurface::SetText(const System::string& text)
		{
			m_text = text;
			return RenderTextToTexture();
		}


		bool TextSurface::Save(std::ostream& stream) const
		{
			return true;
		}

		bool TextSurface::Load(std::istream& stream)
		{
			return true;
		}
	}
}
