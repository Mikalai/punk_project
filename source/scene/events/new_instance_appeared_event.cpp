//#include "new_instance_appeared_event.h"
//
//namespace Scene
//{
//    std::queue<NewInstanceAppearedEvent*> NewInstanceAppearedEvent::eventPool;
//
//    NewInstanceAppearedEvent::NewInstanceAppearedEvent()
//    {
//		eventCode = System::EVENT_INSTANCE_APPEARED;
//    }
//
//    void NewInstanceAppearedEvent::Release()
//    {
//        this->eventPool.push(this);
//    }
//
//    NewInstanceAppearedEvent* NewInstanceAppearedEvent::Raise()
//    {
//        if (eventPool.empty())
//        {
//            NewInstanceAppearedEvent* event = new NewInstanceAppearedEvent();
//            return event;
//        }
//        else
//        {
//            NewInstanceAppearedEvent* event = eventPool.front();
//            eventPool.pop();
//            return event;
//        }
//    }
//
//	System::string NewInstanceAppearedEvent::ToString()
//	{
//		return System::string();
//	}
//}
