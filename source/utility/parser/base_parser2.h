#ifndef _H_PUNK_VIRTUAL_BASE_LOADER_2
#define _H_PUNK_VIRTUAL_BASE_LOADER_2

#include "../../config.h"
#include "../../virtual/interface.h"
namespace System 
{ 
	class string; 
	class Object;
}


namespace Utility
{
	extern PUNK_ENGINE_API System::Object* ParsePunkFile(const System::string& path);
}

#endif	//	_H_PUNK_VIRTUAL_BASE_LOADER_2
