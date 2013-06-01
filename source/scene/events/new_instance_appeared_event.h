//#ifndef SCENE_NEW_INSTANCE_APPEARED_EVENT_H
//#define SCENE_NEW_INSTANCE_APPEARED_EVENT_H
//
//#include "../config.h"
//#include "../../system/handle.h"
//#include "../../system/events/event.h"
//
//namespace Scene
//{
//	class LIB_SCENE NewInstanceAppearedEvent : public System::Event
//    {
//        static std::queue<NewInstanceAppearedEvent*> eventPool;
//        NewInstanceAppearedEvent();
//        NewInstanceAppearedEvent(const NewInstanceAppearedEvent&);
//    public:
//		System::Descriptor parent;
//		System::Descriptor instance;
//		virtual void Release();
//		virtual System::string ToString();
//        static NewInstanceAppearedEvent* Raise();
//    };
//}
//
//#endif // KEY_CHAR_EVENT_H
