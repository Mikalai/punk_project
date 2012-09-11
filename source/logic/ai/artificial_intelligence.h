#ifndef _H_ARTIFICIAL_INTELLIGENCE
#define _H_ARTIFICIAL_INTELLIGENCE

#include "../task/task.h"
#include <queue>

namespace Logic
{
	class Simulation;

	class ArtificialIntelligence
	{
	public:
	
		typedef std::priority_queue<Task*> TaskCollection;
	
	private:
		
		TaskCollection m_tasks;

	public:

		virtual void SetSimulation(Simulation* e) = 0;
		virtual void Solve(float delta_in_ms) = 0;
	
		TaskCollection& GetTaskCollection();
		const TaskCollection& GetTaskCollection() const;
	};
}

#endif
