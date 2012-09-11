#ifndef _H_PUNK_LOGIC_QUEST
#define _H_PUNK_LOGIC_QUEST

#include "config.h"
#include <memory>

namespace System
{
	class string;
	class Buffer;
	class ID;
}

namespace Logic
{
	class PUNK_LOGIC_MODULE Quest
	{
		struct QuestImpl;
		std::auto_ptr<QuestImpl> impl_quest;
	public:
		Quest();
		Quest(const Quest& quest);
		Quest& operator = (const Quest& quest);

		void AddSubQuest(Quest* quest);
		bool IsComplete();
		const System::ID& GetID() const; 
		void SetID(const System::ID& id);
		void SetOwner(const System::ID& c);
		const System::ID& GetOwner() const;

		virtual const System::string ToString() const;				
		virtual System::string& GetDescription();
		
		virtual void Update() = 0;
		virtual std::auto_ptr<Quest> Clone() = 0;
		
		virtual void Save(System::Buffer& buffer);
		virtual void Load(System::Buffer& buffer);

		virtual ~Quest();
	};
}

#endif