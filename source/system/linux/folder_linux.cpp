#ifdef __linux__
#include <dirent.h>
#include <string.h>
#include "folder.h"

Folder::Folder() : dir(0)
{
}

bool Folder::Open(const char *name)
{
    if (dir)
    {
        closedir(dir);
        dir = 0;
    }

    dir = opendir(name);
    if (dir == 0)
        return false;

    folderName = name;
}

bool Folder::IsContain(const char *name) const
{
    if (dir == 0)
        return false;
    rewinddir(dir);

    dirent* dire = 0;
    while (dire = readdir(dir))
    {
        if (!strcmp(name, dire->d_name))
            return true;
    }
    return false;
}

void Folder::Close()
{
    closedir(dir);
    dir = 0;
}

std::list<std::string> Folder::ListAllItems()
{
    std::list<std::string> res;
    if (dir == 0)
    {
        res.push_back("error");
        return res;
    }

    rewinddir(dir);

    dirent* dire = 0;
    while (dire = readdir(dir))
    {
        res.push_back(dire->d_name);
    }

    return res;
}

const char* Folder::Name() const
{
    return folderName.c_str();
}

std::list<std::string> Folder::Find(const char *name) const
{
    std::list<std::string> res;
    if (dir == 0)
    {
        res.push_back("error");
        return res;
    }

    rewinddir(dir);

    dirent* dire = 0;
    while (dire = readdir(dir))
    {
        if (strstr(dire->d_name, name))
            res.push_back(dire->d_name);
    }

    return res;
}

#endif
