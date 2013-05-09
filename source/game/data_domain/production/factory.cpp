#ifdef USE_PRODUCTION

#include <iostream>
#include "factory.h"
#include "human.h"
#include "inventory.h"

Factory::Factory(FactoryClass *c)
    : Entity(c)
    , m_production_cycle(10)
    , m_produced_entities(0)
    , m_production_state(0)
{
}

void Factory::StartWorking(Human *human)
{
    if (IsHired(this, human))
    {
        m_at_work.insert(human);
        std::cout << human << " start working" << std::endl;
    }
}

void Factory::EndWorking(Human *human)
{
    if (IsHired(this, human))
    {
        m_at_work.erase(human);
        std::cout << human << " stop working" << std::endl;
    }
}

void Factory::Update(float dt)
{
    for (auto worker : m_at_work)
    {
        m_production_state += dt;

        if (m_production_state >= m_production_cycle)
        {
            m_production_state = 0;
            ++m_produced_entities;
        }
    }
}

bool Factory::IsAtWork(Human *human)
{
    for (auto worker : m_at_work)
    {
        Human* w = dynamic_cast<Human*>(worker);
        if (w == human)
        {
            return true;
        }
    }
    return false;
}

int Factory::GetProducedCount() const
{
    return m_produced_entities;
}

const Factory::FactoryOutput Factory::CollectProduction(int count)
{
    FactoryOutput result;
    result.item_class = m_output;
    if (count > m_produced_entities)
    {
        result.count = m_produced_entities;
        m_produced_entities = 0;
    }
    else
    {
        result.count = count;
        m_produced_entities -= count;
    }
    return result;
}

void Hire(Factory *factory, Human *human, JobPosition *position)
{    
    //  human already hired
    if (IsHired(human))
        return;

    position->SetA(factory);
    position->SetB(human);
    factory->AddRelation(position);
    human->AddRelation(position);
}

void Fire(Factory *factory, Human *human)
{
    JobPosition* position = nullptr;
    for (auto relation : human->GetRelations())
    {
        position = dynamic_cast<JobPosition*>(relation);
        if (position && position->GetA() == factory)
        {
            position->SetA(nullptr);
            position->SetB(nullptr);
            factory->RemoveRelation(position);
            human->RemoveRelation(position);
        }
    }
}

bool IsHired(Factory *factory, Human* human)
{
    const std::set<Relation*>& relations = factory->GetRelations();

    for (auto relation : relations)
    {
        JobPosition* position = dynamic_cast<JobPosition*>(relation);
        if (position)
        {
            if (position->GetB() == human)
            {
                return true;
            }
        }
    }

    return false;
}

bool IsHired(Human *human)
{
    std::set<Relation*> relations = human->GetRelations();
    for (auto relation : relations)
    {
        JobPosition* position = dynamic_cast<JobPosition*>(relation);
        if (position)
        {
            return true;
        }
    }
    return false;
}

FactoryStaff& Factory::GetFactoryStaff()
{
    return m_staff;
}

#endif //    USE_PRODUCTION
