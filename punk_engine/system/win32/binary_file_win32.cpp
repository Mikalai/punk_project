#ifndef _H_PUNK_BINARY_FILE
#define _H_PUNK_BINARY_FILE

//#include "../allocator.h"
#include "../error.h"
#include "binary_file_win32.h"

namespace System
{
	bool BinaryFile::Load(const string& filename, Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			throw SystemError(L"Error in binary file, can't load it " + filename);
		}

		int size = GetFileSize(hFile, 0);
		buffer.SetSize(size);

		DWORD read;
		if (!ReadFile(hFile, buffer.StartPointer(), size, &read, 0))
		{
			throw SystemError(L"Error in binary file, can't read data " + filename);
		}

		if (read != size)
		{
			throw SystemError(L"Error in binary file, read data less than file contains, possible bad staff happenes " + filename);
		}

		CloseHandle(hFile);
		error = GetLastError();
		return true;
	}

	bool BinaryFile::Save(const string& filename, const Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			throw SystemError(L"Error in binary file, open file for saving " + filename);
		}

		DWORD read;
		if (!WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0))
		{
			throw SystemError(L"Error in binary file, can't write data to file " + filename);
			DWORD error = GetLastError();
		}

		if (read != buffer.GetPosition())
		{
			throw SystemError(L"Error in binary file, written data is less than should be " + filename);
		}

		CloseHandle(hFile);
		error = GetLastError();
		return true;
	}

	bool BinaryFile::Append(const string& filename, const Buffer& buffer)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			throw SystemError(L"Error in binary file, can't open file for appending it " + filename);
		}

		DWORD offset = GetFileSize(hFile, 0);
		SetFilePointer(hFile, offset, 0, FILE_BEGIN);

		DWORD read;

		if (!WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0))
		{
			throw SystemError(L"Error in binary file, can't write data to file " + filename);
		}

		if (read != buffer.GetPosition())
		{
			throw SystemError(L"Error in binary file, written data is less than should be in " + filename);
		}

		CloseHandle(hFile);
		error = GetLastError();
		return true;
	}

	bool BinaryFile::Truncate(const string& filename)
	{
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND)
			return true;

		if (hFile == INVALID_HANDLE_VALUE)
		{
			throw SystemError(L"Error can't truncate binary file " + filename);
		}

		CloseHandle(hFile);
		error = GetLastError();
		return true;
	}
}

#endif