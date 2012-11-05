#ifndef FOLDER_WIN32_H
#define FOLDER_WIN32_H

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <list>
#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE Folder
	{    
		Folder(const Folder&);
		Folder& operator = (const Folder&);
		System::string folderName;
		System::string prevFolder;
	public:
		Folder();
		bool IsContain(const System::string&) const;
		std::list<System::string> ListAllItems();
		bool Open(const System::string& name);    
		void Close();
		std::list<System::string> Find(const System::string& name) const;
		const System::string& Name() const;

		static void DeleteFile(const System::string& filename);
	};
}

#endif // FOLDER_H
