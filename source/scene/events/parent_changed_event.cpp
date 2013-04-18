//#include "parent_changed_event.h"
//
//namespace Scene
//{
//    std::queue<ParentChangedEvent*> ParentChangedEvent::eventPool;
//
//    ParentChangedEvent::ParentChangedEvent()
//    {
//		eventCode = System::EVENT_INSTANCE_CHANGED_PARENT;
//    }
//
//    void ParentChangedEvent::Release()
//    {
//        this->eventPool.push(this);
//    }
//
//    ParentChangedEvent* ParentChangedEvent::Raise()
//    {
//        if (eventPool.empty())
//        {
//            ParentChangedEvent* event = new ParentChangedEvent();
//            return event;
//        }
//        else
//        {
//            ParentChangedEvent* event = eventPool.front();
//            eventPool.pop();
//            return event;
//        }
//    }
//
//	System::string ParentChangedEvent::ToString()
//	{
//		return System::string::Format(L"ParentChangedEvent: Old parent: (%d, %d); New parent: (%d, %d); Instance: (%d, %d)",
//			old_parent.Type(), old_parent.Number(), new_parent.Type(), old_parent.Number(), instance.Type(), instance.Number());
//	}
//}
