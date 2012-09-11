#include "quest.h"
#include "../system/string.h"
#include "condition.h"

namespace Logic
{
	struct Quest::QuestImpl
	{
		bool m_is_complete;
		std::auto_ptr<Condition> m_condition;
		std::auto_ptr<Quest> m_next_quest;
		
		QuestImpl();
	};

	const System::string Quest::ToString() const
	{
		return L"No string";
	}	
}