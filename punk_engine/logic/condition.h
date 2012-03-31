#ifndef _H_PUNK_LOGIC_CONDITION
#define _H_PUNK_LOGIC_CONDITION

#include "config.h"

namespace Logic
{
	class Condition 
	{
	public:
		virtual bool operator () () = 0;
		virtual ~Condition() {};
	};
}

#endif