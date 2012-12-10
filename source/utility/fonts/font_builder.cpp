#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../system/system.h"
#include "font_builder.h"

namespace Utility
{
	FontBuilder* FontBuilder::m_instance;

	FontBuilder* FontBuilder::Instance()
	{
		if (!m_instance)
			m_instance = new FontBuilder;
		return m_instance;
	}

	void FontBuilder::Destroy()
	{
		delete m_instance;
		m_instance = 0;
	}
	struct CacheData
	{
		unsigned char* buffer;
		int width;
		int height;
		int x_offset;
		int y_offset;
		int x_advance;
		int y_advance;
	}; 

	FT_Library library;
	
	std::map<System::string, FT_Face> fontFace;

	FT_Face curFace;	
	int curSize;
	std::map<int, std::map<void*, std::map<char, CacheData*> > > cache;
	std::map<int, std::map<void*, std::map<wchar_t, CacheData*> > > wcache;

	FontBuilder::FontBuilder()
	{
		Init();
	}

	void FontBuilder::SetCurrentFace(const System::string& fontName)
	{
		FT_Face f = fontFace[fontName];
		if (f != 0)
			curFace = f;
	}

	void FontBuilder::SetCharSize(int width, int height)
	{
		curSize = width * 1000 + height;
		FT_Error error = FT_Set_Char_Size(curFace, width*64, height*64, 96, 96);
		if (error)
			out_error() << L"Can't set new char size" << std::endl;
	}

	void FontBuilder::CacheSymbol(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
		{
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, s);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
				out_error() << L"Error occured while loading a glyph" << std::endl;

			if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
					out_error() << L"Error occured while rendering a glyph" << std::endl;
			}		

			FT_GlyphSlot slot = curFace->glyph;

			data = new CacheData;
			data->width = slot->bitmap.width;
			data->height = slot->bitmap.rows;
			if (data->width*data->height > 0)
			{
				data->buffer = new unsigned char[data->width*data->height];
				memcpy(data->buffer, slot->bitmap.buffer, data->width*data->height);
			}
			data->x_offset = slot->bitmap_left;
			data->y_offset = slot->bitmap_top;
			data->x_advance = slot->advance.x >> 6;
			data->y_advance = slot->advance.y >> 6;

			wcache[curSize][curFace][s] = data;
		}
	}

	int FontBuilder::CalculateLength(const wchar_t* text)
	{
		int res = 0;
		const wchar_t* cur = text;
		while (*cur)
		{
			CacheData* data = wcache[curSize][curFace][*cur];
			
			if (!data)
				CacheSymbol(*cur);	

			data = wcache[curSize][curFace][*cur];			
			res += data->x_advance;
			cur++;
		}
		return res;
	}

	int FontBuilder::GetWidth(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);	

		data = wcache[curSize][curFace][s];			
		return data->x_advance;
	}

	int FontBuilder::GetHeight(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);	

		data = wcache[curSize][curFace][s];			
		return data->height + data->y_offset;
	}

	void FontBuilder::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
		CacheData* data = cache[curSize][curFace][symbol];
		if (!data)
		{
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, symbol);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
				out_error() << L"Error occured while loading a glyph" << std::endl;

			if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
					out_error() << L"Error occured while rendering a glyph" << std::endl;
			}		

			//System::Logger::Instance()->WriteDebugMessage("bitmap (%d; %d)", curFace->glyph->bitmap.width, curFace->glyph->bitmap.rows);

			FT_GlyphSlot slot = curFace->glyph;

			data = new CacheData;
			data->width = slot->bitmap.width;
			data->height = slot->bitmap.rows;
			if (data->width*data->height > 0)
			{
				data->buffer = new unsigned char[data->width*data->height];
				memcpy(data->buffer, slot->bitmap.buffer, data->width*data->height);
			}
			data->x_offset = slot->bitmap_left;
			data->y_offset = slot->bitmap_top;
			data->x_advance = slot->advance.x >> 6;
			data->y_advance = slot->advance.y >> 6;

			cache[curSize][curFace][symbol] = data;
		}

		data = cache[curSize][curFace][symbol];
		*width = data->width;
		*height = data->height;
		*x_offset = data->x_offset;
		*y_offset = data->y_offset;
		*x_advance = data->x_advance;
		*y_advance = data->y_advance;
		*buffer = data->buffer;
		//putchar('\n');/**/
	}
	
	void FontBuilder::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
		CacheData* data = wcache[curSize][curFace][symbol];
		if (!data)
			CacheSymbol(symbol);

		data = wcache[curSize][curFace][symbol];
		*width = data->width;
		*height = data->height;
		*x_offset = data->x_offset;
		*y_offset = data->y_offset;
		*x_advance = data->x_advance;
		*y_advance = data->y_advance;
		*buffer = data->buffer;
		//putchar('\n');/**/
	}

	void FontBuilder::Init()
	{
		System::string iniFontsFile;
		System::string pathToFonts;

		System::ConfigFile conf;
		
		conf.Open(System::Window::Instance()->GetTitle());
		if (conf.IsExistOption(L"fonts"))
		{
			if (conf.ReadOptionString(L"fonts", pathToFonts))
			{
				iniFontsFile = pathToFonts + L"fonts.ini";
			}
		}
		else
		{
			iniFontsFile = (pathToFonts = "d:\\project\\data\\font\\");
			conf.WriteOptionString(L"fonts", iniFontsFile);
		}
		conf.Close();

		FT_Error error = FT_Init_FreeType(&library);
		if (error)
		{
			out_error() << L"Error occured during freetype initialization" << std::endl;
		}

		
		System::Buffer buffer;
		System::BinaryFile::Load(iniFontsFile, buffer);

		while(!buffer.IsEnd())
		{
			System::string name = buffer.ReadWord();
			System::string path = pathToFonts + buffer.ReadWord();
			out_message() << L"Loading font " + path << std::endl;
			
			FT_Face face;

			char ansi[1024];
			int len = 1024;
			path.ToANSI(ansi, len);
			error = FT_New_Face(library, ansi, 0, &face);

			if (error == FT_Err_Unknown_File_Format)
			{
				out_error() << L"The font file could be opened, but it appears that it's font format is unsupported" << std::endl;
			}
			else if (error)
			{
				out_error() << L"The font file could not be opened" << std::endl;
			}

			error = FT_Set_Char_Size(face, 16*64, 16*64, 300, 300);

			if (error)
			{
				out_error() << L"Can't set char size" << std::endl;
			}

			out_message() << L"Font style: " + System::string(face->style_name) << std::endl;
			out_message() << System::string::Format(L"Num glyphs: %d", face->num_glyphs) << std::endl;

			curFace = face;
			fontFace[name] = face;
		}
	}
}