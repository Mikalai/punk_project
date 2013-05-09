#ifdef USE_HUMANS

#ifndef FEMALECLASS_H
#define FEMALECLASS_H

#include "humanclass.h"

namespace Humans
{

class Female;

class FemaleClass final : public HumanClass
{
public:
    FemaleClass(const std::string& name = "FemaleClass") : HumanClass(name) {}
    Female* Create(const std::string name, int age);

    virtual void Register(Entity *value) override;
    virtual void Unregister(Entity *value) override;
    virtual void Destroy(Entity* value) override;

    static void PrintAll();

    static std::vector<Female*>& AllFemales();

private:
    static std::vector<Female*> m_all_females;
};

}
#endif // FEMALECLASS_H

#endif  //  USE_HUMANS
