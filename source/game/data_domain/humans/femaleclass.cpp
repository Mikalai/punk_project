#include <algorithm>
#include <iostream>
#include "femaleclass.h"
#include "female.h"

namespace Humans
{

std::vector<Female*> FemaleClass::m_all_females;

Female* FemaleClass::Create(const std::string name, int age)
{
    std::auto_ptr<Female> female(new Female(this));
    female->SetName(name);
    female->SetAge(age);

    Register(female.get());

    return female.release();
}

void FemaleClass::Destroy(Entity *value)
{
    value->GetClass()->Unregister(value);
    delete value;
}

void FemaleClass::Register(Entity *value)
{
    m_all_females.push_back(dynamic_cast<Female*>(value));
    HumanClass::Register(value);
}

void FemaleClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_females.begin(), m_all_females.end(), dynamic_cast<Female*>(value));
    if (it == m_all_females.end())
        return;
    m_all_females.erase(it);

    HumanClass::Unregister(value);
}

void  FemaleClass::PrintAll()
{
    for (auto female : m_all_females)
    {
        std::cout << "Female: " << female->GetName() << std::endl;
    }
}

std::vector<Female*>& FemaleClass::AllFemales()
{
    return m_all_females;
}

}
