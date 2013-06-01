#include <iostream>
#include <sstream>
#include "gamesimulator.h"
#include "humansimulator.h"

GameSimulator::GameSimulator()
    : m_max_human_count(10)
{
}

void GameSimulator::SetHumanCount(int value)
{
    m_max_human_count = value;
}


void GameSimulator::Update(double time, double dt)
{
    while (Humans::HumanClass::AllHumans().size() < m_max_human_count)
    {
        int k = rand() % 2;
        if (k)
        {
            std::stringstream name;
            name << "Male " << Humans::MaleClass::AllMales().size();
            auto h = m_male_class.Create(name.str(), 18 + rand() % 40);
            m_human_sims.push_back(new HumanSimulator(h));
            std::cout << name.str() << " joined the game" << std::endl;
        }
        else
        {
            std::stringstream name;
            name << "Female " << Humans::FemaleClass::AllFemales().size();
            auto h = m_female_class.Create(name.str(), 18 + rand() % 40);
            m_human_sims.push_back(new HumanSimulator(h));
            std::cout << name.str() << " joined the game" << std::endl;
        }
    }

    auto it = m_human_sims.begin();
    while (it != m_human_sims.end())
    {
        HumanSimulator*& sim = *it;
        sim->Update(time, dt);
        if (sim->NeedToDelete())
        {
            delete sim;
            sim = nullptr;
            std::swap(sim, m_human_sims.back());
            m_human_sims.pop_back();    //  i hope this won't realloc data
        }
        else
            ++it;
    }
}
