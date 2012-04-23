#include <Windows.h>
#include <DbgHelp.h>
#include "stack_trace_win32.h"
#include "../logger.h"

namespace System
{
	Stack::Stack()
	{
		if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
			Logger::GetInstance()->WriteDebugMessage(L"Unable to find initialize debug info", LOG_LOCATION);
	}

	Stack::~Stack()
	{
		SymCleanup(GetCurrentProcess());
	}

	string Stack::GetStackTrace()
	{
	
		string result;
		CONTEXT c;
		memset(&c, 0, sizeof(c));
		RtlCaptureContext(&c);
		STACKFRAME64 stack_frame;
		memset(&stack_frame, 0, sizeof(stack_frame));
		stack_frame.AddrPC.Offset = c.Eip;
		stack_frame.AddrPC.Mode = AddrModeFlat;
		stack_frame.AddrFrame.Offset = c.Ebp;
		stack_frame.AddrFrame.Mode = AddrModeFlat;
		stack_frame.AddrStack.Offset = c.Esp;
		stack_frame.AddrStack.Mode = AddrModeFlat;



#ifdef _M_AMD64
		StackWalk64();
#endif
#ifdef _M_IX86
	/*	if (!StackWalk64(IMAGE_FILE_MACHINE_I386, 
			GetCurrentProcess(),
			GetCurrentThread(),
			&stack_frame,
			&c, 
			0,
			0,
			0,
			0))
		{
			return string(L"Can't make stack trace");
		}*/

		IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64)+1024);
		memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
		pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
		pSym->MaxNameLength = 1024;
		
		IMAGEHLP_LINE64 line;
		memset(&line, 0, sizeof(line));
		line.SizeOfStruct = sizeof(line);

		for (int i = 0; ; i++)
		{
			result += L"\n";
			if (!StackWalk64(IMAGE_FILE_MACHINE_I386, 
				GetCurrentProcess(),
				GetCurrentThread(),
				&stack_frame,
				&c, 
				0,
				SymFunctionTableAccess64,
				SymGetModuleBase64,
				0))
			{
				result += string(L"Can't make stack trace");
				break;
			}

			if (stack_frame.AddrPC.Offset != 0)
			{
				
				DWORD64 displacement;
				if (SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym))
				{
					char buf[1024];
					result += string(pSym->Name) + L" ";
					UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_NAME_ONLY); 
					result += string(buf) + L" ";
					UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_COMPLETE);
					result += string(buf) + L" ";
				}
				else
				{
					result += string(L"Error in SymGetSymFromAddr64");
				}

				DWORD displ = 0;
				if (SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line))
				{
					result += string::Convert((int)line.LineNumber, 10) + L" ";
					result += string(line.FileName) + L" ";
				}
				else
				{
					result += string(L"Error in SymGetLineFromAddr64");
				}

				IMAGEHLP_MODULE64 module;
				memset(&module, 0, sizeof(module));
				module.SizeOfStruct = sizeof(module);

				if (SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module))
				{
					result += string(module.ModuleName) + L" ";
					result += string(module.LoadedImageName) + L"\n";
				}
			}
			
			if (stack_frame.AddrReturn.Offset == 0)
				break;
							

		}

		free(pSym);

#endif

		return result;
	}
}