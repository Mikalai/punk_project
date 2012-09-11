#ifndef _H_PUNK_LOGIC_TREE
#define _H_PUNK_LOGIC_TREE

#include "simulation.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE Tree : public Simulation
	{
	public:
		enum State { NORMAL, BROKEN };
		float m_phi;
		float m_psy;		
		int m_wood_count;
	public:
		Tree();

		float GetPhi() const { return m_phi; }
		float GetPsy() const { return m_psy; }
		int GetWoodResource() const { return m_wood_count; }
		void AddWoodCount(int count) { m_wood_count += count; }

		virtual PostUpdateAction Update(float delta);
	};
}

#endif //	_H_PUNK_LOGIC_TREE