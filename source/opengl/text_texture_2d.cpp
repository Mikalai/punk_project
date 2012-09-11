#include "../utility/fonts/font_builder.h"
#include "text_texture_2d.h"

namespace OpenGL
{
	const System::string& TextTexture2D::GetText() const
	{
		return m_text;
	}

	void TextTexture2D::RenderText(const System::string& value, int font_size, const System::string font_name)
	{
		m_text = value;
		int x = 0;
		int y = GetHeight() - font_size;
		Fill(0);
		Utility::FontBuilder::Instance()->SetCurrentFace(font_name);
		Utility::FontBuilder::Instance()->SetCharSize(font_size, font_size);
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
			if (x + x_offset + width >= GetWidth())
			{
				y -= font_size;
				x = 0;
				if (y < 0)
					return;
			}				
			CopyFromCPU(x + x_offset,  GetHeight() - (y + y_offset), width, height, ImageModule::IMAGE_FORMAT_RED, buffer);
			x += x_advance;				
		}
	}
}