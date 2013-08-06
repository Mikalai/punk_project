#ifdef USE_HUMANS

#ifndef MALE_H
#define MALE_H

#include "human.h"

namespace Humans
{

class MaleClass;

class Male final : public Human
{
public:
    Male(MaleClass* c);
};

}

#endif // MALE_H

#endif  // USE_HUMANS
