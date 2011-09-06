#ifdef _WIN32
#include <string.h>
#include "folder_win32.h"

namespace System
{
	Folder::Folder()
	{
	}

	bool Folder::Open(const char *name)
	{
		return SetCurrentDirectoryA(name) == TRUE;
	}

	bool Folder::IsContain(const char *name) const
	{
		WIN32_FIND_DATAA dir;
		HANDLE file;

		char dirName[256];
		GetCurrentDirectoryA(256, dirName);
		file = FindFirstFileA(dirName, &dir);

		do
		{
			if (!strcmp(name, dir.cFileName))
				return true;
		}
		while (FindNextFileA(file, &dir));

		return false;
	}

	void Folder::Close()
	{

	}

	std::list<std::string> Folder::ListAllItems()
	{
		std::list<std::string> res;
		WIN32_FIND_DATAA dir;
		char dirName[256];
		GetCurrentDirectoryA(256, dirName);
		HANDLE file = FindFirstFileA(dirName, &dir);

		do
		{
			res.push_back(dir.cFileName);
		}
		while (FindNextFileA(file, &dir));

		return res;
	}

	const char* Folder::Name() const
	{
		return folderName.c_str();
	}

	std::list<std::string> Folder::Find(const char *name) const
	{
		std::list<std::string> res;
		WIN32_FIND_DATAA dir;
		char dirName[256];
		GetCurrentDirectoryA(256, dirName);
		HANDLE file = FindFirstFileA(dirName, &dir);

		do
		{
			if (strstr(dir.cFileName, name))
				res.push_back(dir.cFileName);
		}
		while (FindNextFileA(file, &dir));

		return res;
	}
}

#endif
