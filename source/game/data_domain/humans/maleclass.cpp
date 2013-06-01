#ifdef USE_HUMANS

#include <algorithm>
#include <iostream>
#include "maleclass.h"
#include "male.h"

namespace Humans
{

std::vector<Male*> MaleClass::m_all_males;

Male* MaleClass::Create(const std::string name, int age)
{
    std::auto_ptr<Male> male(new Male(this));
    male->SetName(name);
    male->SetAge(age);

    Register(male.get());

    return male.release();
}

void MaleClass::Destroy(Entity *value)
{
    value->GetClass()->Unregister(value);
    delete value;
}

void MaleClass::Register(Entity *value)
{
    m_all_males.push_back(dynamic_cast<Male*>(value));
    HumanClass::Register(value);
}

void MaleClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_males.begin(), m_all_males.end(), dynamic_cast<Male*>(value));
    if (it == m_all_males.end())
        return;
    m_all_males.erase(it);

    HumanClass::Unregister(value);
}

void  MaleClass::PrintAll()
{
    for (auto male : m_all_males)
    {
        std::cout << "Male: " << male->GetName() << std::endl;
    }
}

std::vector<Male*> MaleClass::AllMales()
{
    return m_all_males;
}

}

#endif  //  USE_HUMANS
