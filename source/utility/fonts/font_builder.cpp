#include <map>

#ifdef USE_FREETYPE
#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#endif //   USE_FREETYPE

#include "../../string/string.h"
#include "../../system/module.h"
#include "font_builder.h"

namespace Utility
{
    #ifdef USE_FREETYPE

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

    struct FontBuilder::FontBuilderImpl
    {
        FT_Library library;

        std::map<System::string, FT_Face> fontFace;

        FT_Face curFace;
        int curSize;
        std::map<int, std::map<void*, std::map<char, CacheData*> > > cache;
        std::map<int, std::map<void*, std::map<wchar_t, CacheData*> > > wcache;

        FontBuilderImpl();
        ~FontBuilderImpl();
        void CacheSymbol(wchar_t symb);
        void Init();
        void Clear();
		void SetCurrentFace(const System::string& fontName);
		void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		void SetCharSize(int width, int height);
		void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		int CalculateLength(const System::string& text);
		int CalculateHeight(const System::string& text);
		int GetHeight(wchar_t s);
		int GetWidth(wchar_t s);
		int GetMaxOffset(const System::string& s);
		int GetMinOffset(const System::string& s);
		int GetMaxOffset(wchar_t s);
		int GetMinOffset(wchar_t s);
    };

    FontBuilder::FontBuilderImpl::FontBuilderImpl()
    {
        Init();
    }

    FontBuilder::FontBuilderImpl::~FontBuilderImpl()
    {
        Clear();
    }

    void FontBuilder::FontBuilderImpl::Clear()
    {
        if (!FT_Done_FreeType(library))
            out_error() << L"Can't destroy font builder" << std::endl;
    }

    void FontBuilder::FontBuilderImpl::Init()
	{
		System::string iniFontsFile;
		System::string pathToFonts = System::Environment::Instance()->GetFontFolder();

		System::ConfigFile conf;

		iniFontsFile = System::Environment::Instance()->GetFontFolder() + L"fonts.ini";

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
			out_message() << System::string("Num glyphs: %d", face->num_glyphs) << std::endl;

			curFace = face;
			fontFace[name] = face;
		}
	}

	void FontBuilder::FontBuilderImpl::SetCurrentFace(const System::string& fontName)
	{
		FT_Face f = fontFace[fontName];
		if (f != 0)
			curFace = f;
	}

    void FontBuilder::FontBuilderImpl::SetCharSize(int width, int height)
	{
		curSize = width * 1000 + height;
		FT_Error error = FT_Set_Char_Size(curFace, width*64, height*64, 96, 96);
		if (error)
			out_error() << L"Can't set new char size" << std::endl;
	}

    void FontBuilder::FontBuilderImpl::CacheSymbol(wchar_t s)
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

	int FontBuilder::FontBuilderImpl::CalculateLength(const System::string& text)
	{
		int res = 0;		
		for (auto it = text.begin(); it != text.end(); ++it)
		{
			CacheData* data = wcache[curSize][curFace][*it];

			if (!data)
				CacheSymbol(*it);

			data = wcache[curSize][curFace][*it];
			if (res != 0)
				res += data->x_offset;
			res += data->x_advance;
		}
		return res;
	}

	int FontBuilder::FontBuilderImpl::CalculateHeight(const System::string& text)
	{
		int res = 0;
		int min_h = 0;
		int max_h = 0;		
		for (auto it = text.begin(); it != text.end(); ++it)
		{
			CacheData* data = wcache[curSize][curFace][*it];

			if (!data)
				CacheSymbol(*it);

			data = wcache[curSize][curFace][*it];
			if (max_h < data->y_offset)
				max_h = data->y_offset;
			if (min_h > data->y_offset - data->height)
				min_h = data->y_offset - data->height;
		}
		return max_h - min_h;
	}

    int FontBuilder::FontBuilderImpl::GetWidth(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->x_advance ;
	}

	int FontBuilder::FontBuilderImpl::GetHeight(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->height + abs(data->y_offset);
	}

	int FontBuilder::FontBuilderImpl::GetMaxOffset(const System::string& s)
	{
		int res = 0;
		for (int i = 0, max_i = s.Length(); i < max_i; ++i)
		{
			wchar_t c = s[i];
			int v = GetMaxOffset(c);
			if (res < v)
				res = v;
		}
		return res;
	}

	int FontBuilder::FontBuilderImpl::GetMinOffset(const System::string& s)
	{
		int res = 0;
		for (int i = 0, max_i = s.Length(); i < max_i; ++i)
		{
			wchar_t c = s[i];
			int v = GetMinOffset(c);
			if (res > v)
				res = v;
		}
		return res;
	}

	int FontBuilder::FontBuilderImpl::GetMaxOffset(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->y_offset ;
	}

	int FontBuilder::FontBuilderImpl::GetMinOffset(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->y_offset - data->height;
	}

    void FontBuilder::FontBuilderImpl::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
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

    void FontBuilder::FontBuilderImpl::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
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
    #endif // USE_FREETYPE

	FontBuilder::FontBuilder()
	#ifdef USE_FREETYPE
	: impl(new FontBuilderImpl)
	#else
	: impl(nullptr)
	#endif // USE_FREETYPE
	{}

    FontBuilder::~FontBuilder()
    {
        #ifdef USE_FREETYPE
        delete impl;
        impl = nullptr;
        #endif // USE_FREETYPE
    }
	void FontBuilder::SetCurrentFace(const System::string& fontName)
	{
	    #ifdef USE_FREETYPE
	    impl->SetCurrentFace(fontName);
	    #else
        (void)fontName;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::SetCharSize(int width, int height)
	{
        #ifdef USE_FREETYPE
	    impl->SetCharSize(width, height);
	    #else
        (void)width; (void)height;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::CalculateLength(const System::string& text)
	{
        #ifdef USE_FREETYPE
	    impl->CalculateLength(text);
	    #else
        (void)text;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::CalculateHeight(const System::string& text)
	{
        #ifdef USE_FREETYPE
	    impl->CalculateHeight(text);
	    #else
        (void)text;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetWidth(wchar_t s)
	{
        #ifdef USE_FREETYPE
	    impl->GetWidth(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetHeight(wchar_t s)
	{
        #ifdef USE_FREETYPE
	    impl->GetHeight(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMaxOffset(const System::string& s)
	{
        #ifdef USE_FREETYPE
	    impl->GetMaxOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMinOffset(const System::string& s)
    {
        #ifdef USE_FREETYPE
	    impl->GetMinOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMaxOffset(wchar_t s)
	{
        #ifdef USE_FREETYPE
	    impl->GetMaxOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMinOffset(wchar_t s)
	{
        #ifdef USE_FREETYPE
	    impl->GetMinOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
        #ifdef USE_FREETYPE
	    impl->RenderChar(symbol, width, height, x_offset, y_offset, x_advance, y_advance, buffer);
	    #else
        (void)symbol; (void)width; (void)height; (void)x_offset; (void)y_offset; (void)x_advance; (void)y_advance; (void)buffer;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
        #ifdef USE_FREETYPE
	    impl->RenderChar(symbol, width, height, x_offset, y_offset, x_advance, y_advance, buffer);
	    #else
        (void)symbol; (void)width; (void)height; (void)x_offset; (void)y_offset; (void)x_advance; (void)y_advance; (void)buffer;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}
}
