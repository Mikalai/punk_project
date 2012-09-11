#ifndef _H_PUNK_BINARY_FILE_WIN32
#define _H_PUNK_BINARY_FILE_WIN32

#include <iosfwd>
#include "../../string/string.h"
#include "buffer_win32.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE BinaryFile
	{
	public:
		static bool Load(const string& filename, Buffer& buffer);
		static bool Load(std::istream& stream, Buffer& buffer);
		static bool Save(const string& filename, const Buffer& buffer);
		static bool Append(const string& filename, const Buffer& buffer);
		static bool Truncate(const string& filename);
	};
}

#endif