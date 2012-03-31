#ifndef _H_PUNK_LOGIC_BRING_ITEM
#define _H_PUNK_LOGIC_BRING_ITEM

#include "../quest.h"

namespace System
{
	class ID;
}

namespace Logic
{
	class PUNK_LOGIC_MODULE BringItemQuest : public Quest
	{
	public:
				
		BringItemQuest();
		BringItemQuest(const BringItemQuest& quest);
		BringItemQuest& operator = (const BringItemQuest& quest);

		void SetItemToBring(const System::string& item_name);
		void SetReciever(const System::string& reciever_name);

		const System::string& GetItemToBringName() const;
		const System::string& GetRecieverName() const;

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