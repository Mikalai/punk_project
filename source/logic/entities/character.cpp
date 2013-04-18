//#include <iostream>
//#include "../task/task.h"
//#include "character.h"
//#include "../ai/artificial_intelligence.h"
//
//namespace Logic
//{
//	Character::Character()
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		m_ai = 0;
//	}
//
//	Character::Character(const Character& chr)
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//		m_ai = 0;
//	}
//
//	Character& Character::operator = (const Character& chr)
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		if (this != &chr)
//		{
//			ComplexEntity::operator = (chr);
//			m_ai = 0;
//			m_tasks.clear();
//		}
//		return *this;
//	}
//
//	Character::~Character()
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//		delete m_ai;
//	}
//
//	Simulation::PostUpdateAction Character::Update(float delta_in_ms)
//	{
//		DECLARE_PROPERTY_COLLECTION
//
//		/*CRYPT_SORTED_CTL_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG
//		AccessCheckByTypeResultListAndAuditAlarmByHandleW()
//		*/
//
//		if (pc["ALIVE"].AsInt() == 0)
//			return DESTROY;
//
//		if (m_ai)
//			m_ai->Solve(delta_in_ms);
//
//		if (pc["SLEEP"].AsInt() == 0)
//		{
//			std::vector<Task*> old;
//			for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
//			{
//				if ((*it)->Perform(this, delta_in_ms))
//					delete (*it);
//				else
//					old.push_back(*it);
//			}
//			m_tasks = old;
//		}
//		return KEEP;
//	}
//
//	void Character::SetAI(ArtificialIntelligence* ai)
//	{
//		m_ai = ai;
//		m_ai->SetSimulation(this);
//	}
//
//	void Character::AddTask(Task* task)
//	{
//		m_tasks.push_back(task);
//	}
//
//	Character::TaskCollection& Character::GetTaskList()
//	{
//		return m_tasks;
//	}
//
//	const Character::TaskCollection& Character::GetTaskList() const
//	{
//		return m_tasks;
//	}
//
//}
