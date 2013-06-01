
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <Windows.h>
#endif // _WIN32

#include "logger.h"
#include "../string/string.h"
#include "errors/module.h"
#include "folder.h"

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
#ifdef _WIN32
		wchar_t buf[2048];
		GetCurrentDirectory(2048, buf);
		m_prev_folder_name = buf;
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
#endif	//	_WIN32
		throw PunkInvalidArgumentException(L"Can't open folder " + name);
	}

	bool Folder::IsContain(const System::string& name) const
	{

#ifdef _WIN32
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
#endif	//	_WIN32

		return false;
	}

	void Folder::Close()
	{
#ifdef _WIN32
		SetCurrentDirectory(m_prev_folder_name.Data());
#endif	//	_WIN32
	}

	std::list<System::string> Folder::ListAllItems()
	{
		std::list<System::string> res;

#ifdef _WIN32
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
#endif	//	_WIN32

		return res;
	}

	const System::string& Folder::Name() const
	{
		return m_folder_name;
	}

	void Folder::DeleteFile(const System::string& path)
	{
#ifdef _WIN32
		::DeleteFile(path.Data());
#endif	//	_WIN32

	}
	
	std::list<System::string> Folder::Find(const System::string& name) const
	{
		std::list<System::string> res;

#ifdef _WIN32
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
#endif	//	_WIN32

		return res;
	}

	const string Folder::GetCurrentFolder()
	{
		wchar_t buf[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buf);
		return string(buf);
	}

	void Folder::SetCurrentFolder(const string& value)
	{
		SetCurrentDirectory(value.Data());
	}
}
