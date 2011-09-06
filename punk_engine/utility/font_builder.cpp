#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../system/system.h"
#include "font_builder.h"

namespace Utility
{
	SingletoneImplementation(FontBuilder);

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
			throw System::SystemError(L"Can't set new char size" + LOG_LOCATION_STRING);
	}

	void FontBuilder::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
		CacheData* data = cache[curSize][curFace][symbol];
		if (!data)
		{
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, symbol);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
				throw System::SystemError(L"Error occured while loading a glyph" + LOG_LOCATION_STRING);

			if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
					throw System::SystemError(L"Error occured while rendering a glyph" + LOG_LOCATION_STRING);
			}		

			//System::Logger::GetInstance()->WriteDebugMessage("bitmap (%d; %d)", curFace->glyph->bitmap.width, curFace->glyph->bitmap.rows);

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
		{
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, symbol);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
				throw System::SystemError(L"Error occured while loading a glyph" + LOG_LOCATION_STRING);

			if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
					throw System::SystemError(L"Error occured while rendering a glyph" + LOG_LOCATION_STRING);
			}		

			//System::Logger::GetInstance()->WriteDebugMessage("bitmap (%d; %d)", curFace->glyph->bitmap.width, curFace->glyph->bitmap.rows);

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

			wcache[curSize][curFace][symbol] = data;
		}

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
		
		conf.Open(System::Window::GetInstance()->GetTitle());
		if (conf.IsExistOption(L"fonts"))
		{
			iniFontsFile = (pathToFonts = conf.ReadOptionString(L"fonts")) + L"fonts.ini";
		}
		else
		{
			iniFontsFile = (pathToFonts = "E:\\project\\data\\font\\") + L"fonts.ini";
			conf.WriteOptionString(L"fonts", iniFontsFile);
		}
		conf.Close();

		FT_Error error = FT_Init_FreeType(&library);
		if (error)
		{
			throw System::SystemError(L"Error occured during freetype initialization" + LOG_LOCATION_STRING);
		}

		
		System::Buffer buffer;
		System::BinaryFile::Load(iniFontsFile, buffer);

		while(!buffer.IsEnd())
		{
			System::string name = buffer.ReadWord();
			System::string path = buffer.ReadWord();
			System::Logger::GetInstance()->WriteDebugMessage(L"Loading font " + path + LOG_LOCATION_STRING);
			
			FT_Face face;

			char* ansi;
			int len;
			path.ToANSI(ansi, len);
			error = FT_New_Face(library, ansi, 0, &face);
			delete[] ansi;

			if (error == FT_Err_Unknown_File_Format)
			{
				throw System::SystemError(L"The font file could be opened, but it appears that it's font format is unsupported" + LOG_LOCATION_STRING);
			}
			else if (error)
			{
				throw System::SystemError(L"The font file could not be opened" + LOG_LOCATION_STRING);
			}

			error = FT_Set_Char_Size(face, 16*64, 16*64, 300, 300);

			if (error)
			{
				throw System::SystemError(L"Can't set char size" + LOG_LOCATION_STRING);
			}

			System::Logger::GetInstance()->WriteDebugMessage(L"Font style: " + System::string(face->style_name));
			System::Logger::GetInstance()->WriteDebugMessage(System::string::Format(L"Num glyphs: %d", face->num_glyphs));

			curFace = face;
			fontFace[name] = face;
		}
	}
}