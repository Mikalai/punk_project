#include "object_type_desc.h"
#include "../../string/string.h"

namespace Utility
{
	bool ObjectTypeDesc::BuildFromString(const System::string& value)
	{
		std::vector<System::string> tokens = value.Split(L"_");
		return true;
	}
}