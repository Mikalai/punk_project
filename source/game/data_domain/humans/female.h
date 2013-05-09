#ifdef USE_HUMANS

#ifndef FEMALE_H
#define FEMALE_H

#include "human.h"

namespace Humans
{

class FemaleClass;

class Female final : public Human
{
public:
    Female(FemaleClass* c);
};

}

#endif // FEMALE_H

#endif // USE_HUMANS
