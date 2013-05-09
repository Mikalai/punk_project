#ifndef HUMANSIMULATOR_H
#define HUMANSIMULATOR_H

#include "../data_domain/humans/module.h"
#include "simulator.h"

class HumanSimulator : public Simulator
{
public:
    HumanSimulator(Humans::Human* h);

    virtual void Update(double time, double dt) override;

    bool NeedToDelete() const;
    void Stop();
    bool IsStopped() const;

private:
    Humans::Human* m_human;
};

#endif // HUMANSIMULATOR_H
