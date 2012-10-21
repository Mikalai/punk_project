#ifndef _H_PUNK_SYSTEM_GLOBAL_RESOURCE_MANAGER
#define _H_PUNK_SYSTEM_GLOBAL_RESOURCE_MANAGER

#include <memory>
#include <map>
#include "../string/string.h"
#include "../config.h"
#include "hresource.h"

namespace System
{
	class AbstractManager;

	/*class PUNK_ENGINE GlobalManager
	{
	public:

		bool RegisterManager(AbstractManager* manager);
		bool UnregisterManager(AbstractManager* manager);
		StorableData* Load(int type, const string& name);
		AbstractManager* FindManager(int type);

		static GlobalManager* Instance();
		static void Destroy();

	private:

		static std::auto_ptr<GlobalManager> m_instance;
		std::map<int, AbstractManager*> m_managers;
	};*/
}

#endif	//	_H_PUNK_SYSTEM_GLOBAL_RESOURCE_MANAGER