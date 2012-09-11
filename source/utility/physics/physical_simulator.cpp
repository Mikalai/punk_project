#include "physical_simulator.h"
#include "bullet_physical_simulator.h"

namespace Utility
{
	std::auto_ptr<BulletPhysicalSimulator> g_simulator;

	PhysicalSimulator* PhysicalSimulator::Instance()
	{
		if (!g_simulator.get())
		{
			g_simulator.reset(new BulletPhysicalSimulator);
			g_simulator->Init();
		}
		return g_simulator.get();
	}

	void PhysicalSimulator::Destroy()
	{
		g_simulator.reset(0);
	}
}