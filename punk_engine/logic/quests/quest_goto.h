#ifndef _H_PUNK_ENGINE_LOGIC_QUEST_GOTO
#define _H_PUNK_ENGINE_LOGIC_QUEST_GOTO

#include "../quest.h"

namespace System
{
	class ID;
}

namespace Logic
{
	class GotoQuest : public Quest
	{
		struct GotoQuestImpl;
		std::auto_ptr<GotoQuestImpl> impl_goto_quest;
	public:
		GotoQuest();
		GotoQuest(const GotoQuest& quest);
		GotoQuest& operator = (const GotoQuest& quest);

		void SetDestinationRegion(const System::ID& region);

		virtual const System::string ToString() const;				
		virtual System::string& GetDescription();
		
		virtual void Update();
		virtual std::auto_ptr<Quest> Clone();
		
		virtual void Save(System::Buffer& buffer);
		virtual void Load(System::Buffer& buffer);

		virtual ~GotoQuest();
	};
}
#endif