#include "../../system/module.h"
#include "parse_functions.h"

namespace Utility
{
    System::Object* ParsePunkFile(const System::string& path)
    {
        System::Buffer buffer;
        System::BinaryFile::Load(path, buffer);
        return ParseAnything(buffer);
    }
}
