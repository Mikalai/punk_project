#ifndef _H_PUNK_BINARY_FILE
#define _H_PUNK_BINARY_FILE

#include <istream>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include "../errors/module.h"
#include "binary_file_win32.h"

namespace System
{
	bool BinaryFile::Load(std::istream& stream, Buffer& buffer)
	{
		stream.seekg(0, std::ios_base::end);
		std::streamoff size = stream.tellg();
		stream.seekg(0, std::ios_base::beg);
		buffer.SetSize((int)size);
		stream.read(reinterpret_cast<char*>(buffer.StartPointer()), size);
		return true;
	}

	bool BinaryFile::Load(const string& filename, Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, can't load it " + filename);

		int size = GetFileSize(hFile, 0);
		buffer.SetSize(size);

		DWORD read;
		ReadFile(hFile, buffer.StartPointer(), size, &read, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't read data " + filename);

		if (read != size)
			throw OSException(L"Error in binary file, read data less than file contains, possible bad staff happenes " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Binary file load failed " + filename);
		return true;
	}

	bool BinaryFile::Save(const string& filename, const Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, open file for saving " + filename);

		DWORD read;
		WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

		if (read != buffer.GetPosition())
			throw OSException(L"Error in binary file, written data is less than should be " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Saving binary file failed " + filename);
		return true;
	}

	bool BinaryFile::Append(const string& filename, const Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, can't open file for appending it " + filename);

		DWORD offset = GetFileSize(hFile, 0);
		SetFilePointer(hFile, offset, 0, FILE_BEGIN);

		DWORD read;

		WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

		if (read != buffer.GetPosition())
			throw OSException(L"Error in binary file, written data is less than should be in " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to append a file " + filename);
		return true;
	}

	bool BinaryFile::Truncate(const string& filename)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);		
		error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND || error == ERROR_SUCCESS)
			return true;				
		SetLastError(error);
		CHECK_SYS_ERROR(L"Error can't truncate binary file " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to truncate a file " + filename);
		return true;
	}
}

#endif