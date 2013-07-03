#include <ostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#include <DbgHelp.h>
#endif	//	_WIN32
#ifdef __gnu_linux__
#include <execinfo.h>
#endif  //  __gnu_linux__

#include "stack_trace.h"
#include "exceptions.h"

namespace System
{
	Stack::Stack()
	{
#ifdef _WIN32
		if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
			throw PunkException(L"Unable to find initialize debug info");
#endif	//	_WIN32
	}

	Stack::~Stack()
	{
#ifdef _WIN32
		SymCleanup(GetCurrentProcess());
#endif	//	_WIN32
	}

	string Stack::GetStackTrace()
	{
		string result;
#ifdef _WIN32
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
#endif	//	_M_AMD64
#ifdef _M_IX86
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

#endif	//	_M_IX86
#endif //	_WIN32

		return result;
	}

	/// Using ILogger interface StackWalker
	void Stack::Print(std::wostream& stream)
	{
#ifdef _WIN32
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

		IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64)+1024);
		memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
		pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
		pSym->MaxNameLength = 1024;

		IMAGEHLP_LINE64 line;
		memset(&line, 0, sizeof(line));
		line.SizeOfStruct = sizeof(line);
		stream << "Call stack:" << std::endl;
		for (int i = 0; ; i++)
		{
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
				break;
			}

			if (stack_frame.AddrPC.Offset != 0)
			{

				DWORD64 displacement;
				SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym);
				DWORD displ = 0;
				line.FileName = 0;
				line.LineNumber = -1;
				SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line);

				IMAGEHLP_MODULE64 module;
				memset(&module, 0, sizeof(module));
				module.SizeOfStruct = sizeof(module);

				SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module);
				if (i != 0)	
					stream << "[" << i << "] " << module.ModuleName << "->" << ((line.FileName != 0) ? line.FileName : "NULL") << "(" <<  (int)line.LineNumber << ") : " << pSym->Name << std::endl;
			}
			if (stack_frame.AddrReturn.Offset == 0)
				break;
		}
		free(pSym);
#endif	//	_M_IX86
#endif	//	_WIN32
#ifdef __gnu_linux__
        const int s = 100;
        void *array[s];
        size_t size;
        char **strings;
        size_t i;

        size = backtrace (array, s);
        strings = backtrace_symbols (array, size);

        stream << System::string("Obtained {0} stack frames.").arg(size) << std::endl;

        for (i = 0; i < size; i++)
        {
            stream << System::string(strings[i]) << std::endl;
        }

        free (strings);
#endif  //    __gnu_linux__
	}
}
