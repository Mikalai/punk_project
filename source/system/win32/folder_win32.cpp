#ifdef _WIN32
#include "../logger.h"
#include "../../string/string.h"
#include "folder_win32.h"

namespace System
{
	Folder::Folder()
	{
	}

	Folder::~Folder()
	{
		Close();
	}

	bool Folder::Open(const System::string& name)
	{
		wchar_t buf[2048];
		GetCurrentDirectory(2048, buf);
		prevFolder = buf;
		if (SetCurrentDirectory(name.Data()) == TRUE)
		{
			return true;
		}

		//	try to create
		if (CreateDirectory(name.Data(), 0) != 0)
		{
			if (SetCurrentDirectory(name.Data()) == TRUE)
			{
				return true;
			}
		}
	
		return (out_error() << "Can't open folder " << name << std::endl, false);
	}

	bool Folder::IsContain(const System::string& name) const
	{
		WIN32_FIND_DATA dir;
		HANDLE file;

		wchar_t dirName[256];
		GetCurrentDirectory(256, dirName);
		file = FindFirstFile(dirName, &dir);

		do
		{
			if (name == dir.cFileName)
				return true;
		}
		while (FindNextFile(file, &dir));

		return false;
	}

	void Folder::Close()
	{
		SetCurrentDirectory(prevFolder.Data());
	}

	std::list<System::string> Folder::ListAllItems()
	{
		std::list<System::string> res;
		WIN32_FIND_DATA dir;
		wchar_t dirName[256];
		GetCurrentDirectory(256, dirName);
		HANDLE file = FindFirstFile(L"*", &dir);

		if (file != INVALID_HANDLE_VALUE)
		{
			do
			{
				System::string f = System::string(dir.cFileName);
				if (f == L"." || f == L"..")	//skip this and parent
					continue;
				res.push_back(f);
			}
			while (FindNextFile(file, &dir));
		}

		return res;
	}

	const System::string& Folder::Name() const
	{
		return folderName;
	}

	void Folder::DeleteFile(const System::string& path)
	{
		::DeleteFile(path.Data());
	}
	
	std::list<System::string> Folder::Find(const System::string& name) const
	{
		std::list<System::string> res;
		WIN32_FIND_DATA dir;
		wchar_t dirName[256];
		GetCurrentDirectory(256, dirName);
		HANDLE file = FindFirstFile(name.Data(), &dir);

		if (file != INVALID_HANDLE_VALUE)
		{
			do
			{
				System::string f = System::string(dir.cFileName);
				if (f == L"." || f == L"..")	//skip this and parent
					continue;
				//if (wcswcs(dir.cFileName, name.Data()))
				res.push_back(f);
			}
			while (FindNextFile(file, &dir));
		}

		return res;
	}
}

#endif
