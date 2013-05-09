#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "../data_domain/humans/module.h"

class HumanSimulator;

class Simulator
{
public:
    Simulator();

    virtual void Update(double time, double dt) = 0;

private:

};

#endif // SIMULATOR_H
