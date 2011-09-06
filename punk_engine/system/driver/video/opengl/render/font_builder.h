#ifndef _H_FONT_BUILDER
#define _H_FONT_BUILDER

#include "../system/system.h"
#include <map>

namespace Render
{
	class FontBuilder
	{		
	public:
		static void Init(System::string iniFontsFile);
		static void SetCurrentFace(System::string fontName);
		static void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		static void SetCharSize(int width, int height);
		static void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
	};
}

#endif
