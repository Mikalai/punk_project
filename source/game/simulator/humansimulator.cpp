#include <iostream>
#include "humansimulator.h"

#ifdef USE_HUMANS
#include "../data_domain/humans/module.h"
#endif

#ifdef USE_FOOD
#include "../data_domain/food/module.h"
#endif

#ifdef USE_STATE
#include "../data_domain/state/fraction.h"
#endif

#ifdef USE_NATURE
#include "../data_domain/nature/"
#endif

#include "../data_domain/common/module.h"

HumanSimulator::HumanSimulator(Humans::Human* h)
    : m_human(h)
{
    m_human->AddAttribute(new Food::Hunger());
    m_human->AddAttribute(new Food::Thirst());

}

void HumanSimulator::Update(double time, double dt)
{
    if (IsStopped())
        return;

    Food::Hunger* h = GetAttribute<Food::Hunger>(m_human);
    Food::Thirst* t = GetAttribute<Food::Thirst>(m_human);
    double hunger_per_second = 100.0 / (30.0 * 24.0 * 60.0 * 60.0);
    double thirst_per_second = 100.0 / (3.0 * 24.0 * 60.0 * 60.0);
    h->Modify(hunger_per_second);
    if (h->GetCurrentLevel() >= 100.0)
    {
        std::cout << m_human->GetName() << " died from hunger" << std::endl;
        m_human->Die();
        Stop();
        return;
    }

    t->Modify(thirst_per_second);
    if (t->GetCurrentLevel() >= 100.0)
    {
        std::cout << m_human->GetName() << " died from thirst" << std::endl;
        m_human->Die();
        Stop();
        return;
    }

    auto position = GetAttribute<Common::Location>(m_human);
    auto property = Common::FindProperty(m_human);

}

bool HumanSimulator::NeedToDelete() const
{
    return m_human == nullptr;
}

void HumanSimulator::Stop()
{
    m_human = nullptr;
}

bool HumanSimulator::IsStopped() const
{
    return m_human == nullptr;
}
