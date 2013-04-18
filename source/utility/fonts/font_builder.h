#ifndef _H_FONT_BUILDER
#define _H_FONT_BUILDER

#include "../../config.h"
#include <map>

namespace System
{
	class string;
}

namespace Utility
{
	class PUNK_ENGINE FontBuilder final
	{
	public:
		FontBuilder();
		~FontBuilder();
		void Init();
		void SetCurrentFace(const System::string& fontName);
		void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		void SetCharSize(int width, int height);
		void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		int CalculateLength(const wchar_t* text);
		int CalculateHeight(const wchar_t* text);
		int GetHeight(wchar_t s);
		int GetWidth(wchar_t s);
		int GetMaxOffset(const System::string& s);
		int GetMinOffset(const System::string& s);
		int GetMaxOffset(wchar_t s);
		int GetMinOffset(wchar_t s);

    private:

        struct FontBuilderImpl;
        FontBuilderImpl* impl;

	};
}

#endif
