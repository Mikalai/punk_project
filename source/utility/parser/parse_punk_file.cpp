#include "../../system/module.h"
#include "parse_functions.h"

namespace Utility
{
    System::Object* ParsePunkFile(const System::string& path)
    {
        System::Buffer buffer;
        if (!System::BinaryFile::Load(path, buffer))
            return nullptr;
        return ParseAnything(buffer);
    }
}
