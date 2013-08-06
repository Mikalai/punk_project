#ifdef USE_PRODUCTION

#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include "era.h"
#include "factory_staff.h"

class Human;

class EntityClass;
class JobPosition;
class Factory;

class FactoryClass : public EntityClass
{
public:

    virtual void Destroy(Entity* value);
    virtual void Register(Entity* e);
    virtual void Unregister(Entity* e);

private:
    static std::vector<Factory*> m_all_factories;
};

class Factory : public Entity
{
public:

    struct FactoryOutput
    {
        EntityClass* item_class;
        int count;
    };

public:
    Factory(FactoryClass* c);

    void StartWorking(Human* human);
    void EndWorking(Human* human);
    void Update(float dt);
    void SetOutput(Entity* e);

    bool IsAtWork(Human* human);
    int GetProducedCount() const;
    const FactoryOutput CollectProduction(int count);

    FactoryStaff& GetFactoryStaff();
private:

    float m_production_cycle;
    float m_production_state;

    int m_produced_entities;

    EntityClass* m_output;

    /// Humans at work
    std::set<Human*> m_at_work;

    FactoryStaff m_staff;
};

class JobPosition : public Relation
{
};

extern void Hire(Factory* factory, Human* human, JobPosition* position);
extern void Fire(Factory* factory, Human* human);
extern bool IsHired(Factory* factory, Human* human);
extern bool IsHired(Human* human);

#endif // FACTORY_H

#endif  //    USE_PRODUCTION
