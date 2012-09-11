#ifndef _H_FONT_BUILDER
#define _H_FONT_BUILDER

#include "../../config.h"
#include "../../system/singletone.h"
#include <map>

namespace System
{
	class string;
}

namespace Utility
{
	SingletoneInterface(FontBuilder, PUNK_ENGINE);

	class PUNK_ENGINE FontBuilder : public Singletone(FontBuilder)
	{		
	public:
		FontBuilder();
		void Init();
		void SetCurrentFace(const System::string& fontName);
		void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		void SetCharSize(int width, int height);
		void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		int CalculateLength(const wchar_t* text);
		int GetHeight(wchar_t s);
		int GetWidth(wchar_t s);
	private:
		void CacheSymbol(wchar_t symb);
	};
}

#endif
