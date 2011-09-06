#ifndef FOLDER_LINUX_H
#define FOLDER_LINUX_H

#include <string>
#include <list>
#include <dirent.h>

class Folder
{    
    Folder(const Folder&);
    Folder& operator = (const Folder&);
    std::string folderName;
    DIR* dir;
public:
    Folder();
    bool IsContain(const char*) const;
    std::list<std::string> ListAllItems();
    bool Open(const char* name);    
    void Close();
    std::list<std::string> Find(const char* name) const;
    const char* Name() const;
};

#endif // FOLDER_H
