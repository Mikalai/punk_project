#include "resource_manager_win32.h"

namespace System
{
	unsigned ResourceManager::m_instance_id = 1;

	SingletoneImplementation(ResourceManager);
}