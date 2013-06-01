#ifdef USE_HUMANS

#include <iostream>
#include <algorithm>
#include "human.h"
#include "humanclass.h"

namespace Humans
{

Human::Human(HumanClass* c)
    : Entity(c)
    , m_dead(false)
{}

Human::~Human()
{}

//void Human::Update(float dt)
//{
//    static int work_time = 0;
//    work_time += dt;

//    if (work_time > 24)
//        work_time = 0;

//    for (auto relation : GetRelations())
//    {
//        JobPosition* position = dynamic_cast<JobPosition*>(relation);
//        if (position)
//        {
//            Factory* factory = dynamic_cast<Factory*>(relation->GetA());

//            if (work_time > 8 && work_time < 17)
//            {
//                if (!factory->IsAtWork(this))
//                    factory->StartWorking(this);
//            }
//            else if (work_time > 17 && work_time < 24 || work_time < 8)
//            {
//                if (factory->IsAtWork(this))
//                    factory->EndWorking(this);
//            }
//        }
//    }

//}

}

#endif  //  USE_HUMANS
