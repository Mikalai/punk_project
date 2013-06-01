#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#elif defined __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#include <istream>
#include "errors/module.h"
#include "binary_file.h"
#include "buffer.h"

namespace System
{
#ifdef _WIN32
    size_t GetFileSize(HANDLE hFile)
    {
        return (size_t)::GetFileSize(hFile);
    }

    HANDLE OpenReadFile(const System::string& filename)
    {
        HANDLE hFile = CreateFile(filename.Data(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        CHECK_SYS_ERROR(L"Error in binary file, can't load it " + filename);
        return hFile;
    }

    void CloseFile(HANDLE handle)
    {
        CloseHandle(hFile);
        CHECK_SYS_ERROR(L"Binary file load failed " + filename);
    }

    void ReadFile(HANDLE hFile, void* ptr, size_t size)
    {
        ReadFile(hFile, buffer.StartPointer(), size, &read, 0);
        CHECK_SYS_ERROR(L"Error in binary file, can't read data " + filename);

        if (read != (DWORD)size)
            throw OSException(L"Error in binary file, read data less than file contains, possible bad staff happenes " + filename);
    }

#elif defined __linux__
    size_t GetFileSize(int hFile)
    {
        __off_t size = lseek(hFile, 0, SEEK_END);
        return (size_t)size;
    }

    int OpenReadFile(const System::string& filename)
    {
        int hFile = open(&filename.ToUtf8()[0], O_RDONLY);
        return hFile;
    }

    void CloseFile(int handle)
    {
        close(handle);
    }

    void ReadFile(int handle, void* ptr, size_t size)
    {
        size_t res = read(handle, ptr, size);
    }

#endif

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
        auto hFile = OpenReadFile(filename);
        size_t size = GetFileSize(hFile);
        buffer.SetSize(size);
        ReadFile(hFile, buffer.StartPointer(), size);
        CloseFile(hFile);
		return true;
	}

	bool BinaryFile::Save(const string& filename, const Buffer& buffer)
	{
#ifdef _WIN32

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, open file for saving " + filename);

		DWORD read;
		WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

        if (read != (DWORD)buffer.GetPosition())
			throw OSException(L"Error in binary file, written data is less than should be " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Saving binary file failed " + filename);
#endif	//	_WIN32
		return true;
	}

	bool BinaryFile::Append(const string& filename, const Buffer& buffer)
	{
#ifdef _WIN32
		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, can't open file for appending it " + filename);

		DWORD offset = GetFileSize(hFile, 0);
		SetFilePointer(hFile, offset, 0, FILE_BEGIN);

		DWORD read;

		WriteFile(hFile, (LPCVOID)buffer.StartPointer(), (DWORD)buffer.GetPosition(), &read, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

        if (read != static_cast<DWORD>(buffer.GetPosition()))
			throw OSException(L"Error in binary file, written data is less than should be in " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to append a file " + filename);
#endif	//	_WIN32
		return true;
	}

	bool BinaryFile::Truncate(const string& filename)
	{
#ifdef _WIN32
		DWORD error = GetLastError();

		HANDLE hFile = CreateFile(filename.Data(), GENERIC_WRITE, 0, 0, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);		
		error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND || error == ERROR_SUCCESS)
			return true;				
		SetLastError(error);
		CHECK_SYS_ERROR(L"Error can't truncate binary file " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to truncate a file " + filename);
#endif	//	_WIN32
		return true;
	}
}
