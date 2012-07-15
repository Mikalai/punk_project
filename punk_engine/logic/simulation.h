#ifndef _H_SIMULATION
#define _H_SIMULATION

#include "config.h"

namespace System { class Event; }
namespace Logic
{
	class PUNK_LOGIC_MODULE Simulation
	{
	public:
		//	after update it is possible that simulation is not needed in the game anymore
		enum PostUpdateAction {DESTROY, UNMANAGE, KEEP};
			
		virtual PostUpdateAction Update(float delta_in_ms) = 0;	

	};
}

#endif