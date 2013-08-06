#ifndef H_PUNK_SYSTEM_FOLDER
#define H_PUNK_SYSTEM_FOLDER

#include <list>
#include "../string/string.h"
#include "../config.h"

namespace System
{
	class PUNK_ENGINE_API Folder
	{    
		Folder(const Folder&);
		Folder& operator = (const Folder&);
		System::string m_folder_name;
		System::string m_prev_folder_name;
	public:
		Folder();
		~Folder();
		bool IsContain(const System::string&) const;
		std::list<System::string> ListAllItems();
		bool Open(const System::string& name);    
		void Close();
		std::list<System::string> Find(const System::string& name) const;
		const System::string& Name() const;

		static void DeleteFile(const System::string& filename);
		static const string GetCurrentFolder();
		static void SetCurrentFolder(const string& value);
	};
}

#endif // H_PUNK_SYSTEM_FOLDER
