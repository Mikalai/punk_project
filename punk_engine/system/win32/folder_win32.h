#ifndef FOLDER_WIN32_H
#define FOLDER_WIN32_H

#include <Windows.h>
#include <string>
#include <list>
#include "../config.h"

namespace System
{
	class MODULE_SYSTEM Folder
	{    
		Folder(const Folder&);
		Folder& operator = (const Folder&);
		std::string folderName;
	public:
		Folder();
		bool IsContain(const char*) const;
		std::list<std::string> ListAllItems();
		bool Open(const char* name);    
		void Close();
		std::list<std::string> Find(const char* name) const;
		const char* Name() const;
	};
}

#endif // FOLDER_H
