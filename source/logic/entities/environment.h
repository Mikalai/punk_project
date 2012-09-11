#ifndef _H_WORLD
#define _H_WORLD

#include "../config.h"
#include "complex_entity.h"
#include "../simulation.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE Environment : public ComplexEntity, public Simulation
	{
	public:
		typedef std::vector<Simulation*> SimulationCollection;

	private:
		SimulationCollection m_simulations;

	public:
		SimulationCollection& GetSimulationCollection() { return m_simulations; }
		virtual PostUpdateAction Update(float delta_in_ms);
		virtual void AddChild(SolidEntity* child);
		virtual void RemoveChild(SolidEntity* child);
		virtual ~Environment();
	};
}
#endif