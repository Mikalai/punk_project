#ifdef USE_HUMANS

#ifndef MALECLASS_H
#define MALECLASS_H

#include "humanclass.h"

namespace Humans
{

class Male;

class MaleClass final : public HumanClass
{
public:
    MaleClass(const std::string& name = "MaleClass") : HumanClass(name) {}
    Male* Create(const std::string name, int age);

    virtual void Register(Entity *value) override;
    virtual void Unregister(Entity *value) override;
    virtual void Destroy(Entity* value) override;

    static std::vector<Male*> AllMales();

    static void PrintAll();

private:
    static std::vector<Male*> m_all_males;
};

}

#endif // MALECLASS_H

#endif  //  USE_HUMANS
