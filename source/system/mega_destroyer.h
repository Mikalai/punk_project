#ifndef _H_PUNK_SYSTEM_MEGA_DESTROYER
#define _H_PUNK_SYSTEM_MEGA_DESTROYER

#include "../config.h"
#include <stack>
#include <memory>

namespace System
{
	class PUNK_ENGINE MegaDestroyer
	{
	public:
		typedef void (*Destroyer)(void);
	public:

		void PushDestroyer(Destroyer value);
		~MegaDestroyer();

		static MegaDestroyer* Instance();
		static void Destroy();

	private:
		static std::unique_ptr<MegaDestroyer> m_instance;
		std::stack<Destroyer> m_destroyers;
	};
}

#endif	//	_H_PUNK_SYSTEM_MEGA_DESTROYER