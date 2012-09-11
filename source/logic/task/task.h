#ifndef _H_TASK
#define _H_TASK

#include "../config.h"
#include "../../math/vec3.h"
#include "../entities/simple_entity.h"

namespace Logic
{
	class Character;
	class AbstractEntity;
	class ComplexEntity;
	class SolidEntity;

	class PUNK_LOGIC_MODULE Task 
	{
	public:
		double m_priority;
		//	returns true if task complete
		virtual bool Perform(Character* c, float delta_in_ms) = 0;
		virtual const System::string ToString() const = 0;
		virtual ~Task() {}
	};
}

namespace Logic
{
	class PUNK_LOGIC_MODULE TaskGoTo : public Task
	{
		Math::vec3 m_dst;	// in parent space
	public:
		virtual bool Perform(Character* c, float delta_in_ms);
		virtual const System::string ToString() const;
		void SetDestination(const Math::vec3& dst)	{ m_dst = dst; }		
	};

	class PUNK_LOGIC_MODULE TaskEat : public Task
	{
		SolidEntity* m_entity;
	public:
		TaskEat(SolidEntity* e = 0) : m_entity(e) {}
		virtual bool Perform(Character* c, float delta_in_ms);
		virtual const System::string ToString() const;
		void SetEntityToEat(SolidEntity* e) { m_entity = e; }	
	};

	class PUNK_LOGIC_MODULE TaskTake : public Task
	{
		SolidEntity* m_entity;
	public:
		TaskTake(SolidEntity* e) : m_entity(e) {}
		virtual bool Perform(Character* c, float delta_in_ms);
		virtual const System::string ToString() const;
		void SetEntityToTake(SolidEntity* e) { m_entity = e; }
	};

	/*inline bool operator < (const Task& t1, const Task& t2)
	{
		return t1.m_priority < t2.m_priority;
	}*/
}

#endif