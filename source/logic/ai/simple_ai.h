#ifndef _H_SIMPLE_AI
#define _H_SIMPLE_AI

#include "artificial_intelligence.h"

namespace Logic
{
	class Character;

	/// Can be bound to character
	class SimpleAI : public ArtificialIntelligence
	{
		Character* m_character;
		SolidEntity* m_entity_to_goto;
	public:
		SimpleAI();
		virtual void SetSimulation(Simulation* e);
		virtual void Solve(float delta_in_ms);
		void Apply(ComplexEntity* e);
	};
}

#endif
