#ifndef _H_PUNK_BINARY_FILE
#define _H_PUNK_BINARY_FILE

#include <iosfwd>
#include "../string/string.h"
#include "../config.h"

namespace System
{
	class Buffer;

	class PUNK_ENGINE_API BinaryFile
	{
	public:

		static bool Load(const string& filename, Buffer& buffer);
		static bool Load(std::istream& stream, Buffer& buffer);
		static bool Save(const string& filename, const Buffer& buffer);
		static bool Append(const string& filename, const Buffer& buffer);
		static bool Truncate(const string& filename);
	};
}

#endif	//	_H_PUNK_BINARY_FILE
