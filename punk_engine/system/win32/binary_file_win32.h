#ifndef _H_PUNK_BINARY_FILE_WIN32
#define _H_PUNK_BINARY_FILE_WIN32

#include "string_win32.h"
#include "buffer_win32.h"
#include "../config.h"

namespace System
{
	class LIB_SYSTEM BinaryFile
	{
	public:
		static bool Load(const string& filename, Buffer& buffer);
		static bool Save(const string& filename, const Buffer& buffer);
		static bool Append(const string& filename, const Buffer& buffer);
		static bool Truncate(const string& filename);
	};
}

#endif