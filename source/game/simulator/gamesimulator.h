#ifndef GAMESIMULATOR_H
#define GAMESIMULATOR_H

#include "simulator.h"

class GameSimulator : public Simulator
{
public:
    GameSimulator();

    void SetHumanCount(int count);
    virtual void Update(double time, double dt) override;

private:
    std::vector<HumanSimulator*> m_human_sims;

    Humans::MaleClass m_male_class;
    Humans::FemaleClass m_female_class;
    Humans::HumanClass m_human_class;

    int m_max_human_count;
};

#endif // GAMESIMULATOR_H
