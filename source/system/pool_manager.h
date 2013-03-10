#ifndef _H_PUNK_SYSTEM_POOL_MANAGER
#define _H_PUNK_SYSTEM_POOL_MANAGER

#include <vector>
#include <memory>
#include "../config.h"

namespace System
{
	class PUNK_ENGINE PoolManager
	{
	public:
		typedef void (*CleanFunc)(void);
	public:

		//void AddCleaner(CleanFunc func);
		//~PoolManager();
		static PoolManager* Instance();
		static void Destroy();

	private:
		//std::vector<CleanFunc> m_cleaners;
		static std::auto_ptr<PoolManager> m_instance;
	};
}

#endif	//	_H_PUNK_SYSTEM_POOL_MANAGER
