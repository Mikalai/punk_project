#ifndef _H_COUNT_TASKS
#define _H_COUNT_TASKS

#include "../config.h"
#include "visitor.h"
#include <string>

namespace Logic
{
	class PUNK_LOGIC_MODULE CountTasks : public Visitor
	{
		int m_count;
	public:

		CountTasks()
			: m_count(0)
		{}

		virtual bool Visit(AbstractEntity* e) { return true; }
		virtual bool Visit(ComplexEntity* e);
		virtual bool Visit(SimpleEntity* e) { return true; };
		virtual bool Visit(SpaceEntity* e) { return true; };
	};
}

#endif