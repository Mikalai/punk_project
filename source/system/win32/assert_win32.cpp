
//	OS specific

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

//	STL
#include <sstream>

#include "assert_win32.h"
#include "stack_trace_win32.h"
namespace System
{
#ifdef _DEBUG

	int CustomAssertFunction(bool exp, char* description, char* func, int line, char* file)
	{
		Stack walker;
		if (exp)
			return 0;

		std::wstringstream stream;
		stream << description << " at " << file << "(" << line << ") : " << func << std::endl;	
		walker.Print(stream);
		//
		//	copy information in the clipboard
		//
		if (OpenClipboard(NULL))
		{
			HGLOBAL hMem;
			wchar_t* pMem;

			hMem = GlobalAlloc(GHND|GMEM_DDESHARE, stream.str().length()*sizeof(wchar_t)+1);

			if (hMem)
			{
				pMem = (wchar_t*)GlobalLock(hMem);
				wcscpy_s(pMem, stream.str().length()+1, stream.str().c_str());

				GlobalUnlock(hMem);
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hMem);
			}
			CloseClipboard();
			stream << "(Information copied to clipboard)";
		}	

		return MessageBox(0, stream.str().c_str(), L"Assert failed", MB_ICONERROR|MB_ABORTRETRYIGNORE);
	}
	#endif	//	_DEBUG
}
