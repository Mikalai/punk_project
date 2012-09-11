#ifndef _H_ENV_AI
#define _H_ENV_AI

#include "artificial_intelligence.h"

namespace Logic
{
	class EnvironmentAI : public ArtificialIntelligence
	{
		EnvironmentAI* m_env;
	public:
		virtual void SetSimulation(Simulation* e);
		virtual void Solve(int delta_in_ms);
	};
}
#endif