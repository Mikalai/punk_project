#include <sstream>
#include "assert2.h"
#include "stack_trace.h"

namespace System
{

#ifdef WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX

#include <Windows.h>

#ifdef _DEBUG

	int CustomAssertFunction(bool exp, const System::string& description, char* func, int line, char* file)
	{
		Stack walker;
		if (exp)
			return 0;

		std::wstringstream stream;
		stream << description.Data() << L" at " << System::string(file).Data() << L"(" << line << L") : " << System::string(func).Data() << std::endl;	
		walker.Print(stream);
		//
		//	copy information in the clipboard
		//
		if (OpenClipboard(NULL))
		{
			HGLOBAL hMem;
			wchar_t* pMem;

			hMem = GlobalAlloc(GHND|GMEM_DDESHARE, (stream.str().length()+1)*sizeof(wchar_t));

			if (hMem)
			{
				pMem = (wchar_t*)GlobalLock(hMem);
				wcscpy_s(pMem, stream.str().length()+1, stream.str().c_str());

				GlobalUnlock(hMem);
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hMem);
			}
			CloseClipboard();
			stream << L"(Information copied to clipboard)";
		}	

		return MessageBox(0, stream.str().c_str(), L"Assert failed", MB_ICONERROR|MB_ABORTRETRYIGNORE);
	}
#endif	//	_DEBUG
#endif	//	WIN32

}
