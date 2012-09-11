#ifndef _H_PUNK_LOGIC_SIMULATOR
#define _H_PUNK_LOGIC_SIMULATOR

#include <vector>

namespace System { class Event; }

namespace Logic
{
	class Simulation;

	class PUNK_LOGIC_MODULE Simulator
	{
		std::vector<Simulation*> m_simulations;
	public:
		void Add(Simulation* simulation);
		void OnUpdate(System::Event* event);

		void Activate();
		void Deactivate();
	};
}

#endif //	_H_PUNK_LOGIC_SIMULATOR