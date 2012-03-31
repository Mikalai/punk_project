#ifndef _H_PUNK_LOGIC_ACTION_GIVE
#define _H_PUNK_LOGIC_ACTION_GIVE

#include "../config.h"

namespace System
{
	class ID;
	class string;
	class Buffer;
}

namespace Logic
{
	class PUNK_LOGIC_MODULE GiveAction
	{
	public:
		bool operator () (const System::ID& src, const System::ID& dst, const System::string& name, unsigned count);

		const System::string ToString() const;
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);
	};
}

#endif