//#ifndef _H_CHARACTER
//#define _H_CHARACTER
//
//#include "../config.h"
//#include "complex_entity.h"
//#include "../simulation.h"
//
//namespace Logic
//{
//	class ArtificialIntelligence;
//	class Task;
//
//	class PUNK_LOGIC_MODULE Character : public ComplexEntity, public Simulation
//	{
//	public:
//		typedef std::vector<Task*> TaskCollection;
//	protected:
//
//		ArtificialIntelligence* m_ai;
//		TaskCollection m_tasks;
//
//	public:
//
//		Character();
//		Character(const Character& chr);
//		Character& operator = (const Character& chr);
//		virtual ~Character();
//
//		virtual PostUpdateAction Update(float delta_in_ms);
//		void SetAI(ArtificialIntelligence* ai);
//		void AddTask(Task* t);
//		TaskCollection& GetTaskList();
//		const TaskCollection& GetTaskList() const;
//	};
//
//}
//#endif
