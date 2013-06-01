#ifdef USE_STATE

#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <map>
#include "era.h"

class Human;
class Fraction;

class FractionClass : public EntityClass
{
public:

    FractionClass(const std::string& name) : EntityClass(name) {}

    Fraction* Create(const std::string& name);

    virtual void Destroy(Entity* value) override;
    virtual void Unregister(Entity *e) override;
    virtual void Register(Entity *e) override;

    static void PrintAll();

private:
    static std::vector<Fraction*> m_all_fractions;
};

class Fraction : public Entity
{
public:
    int GetAllyNumber() const;
    int GetEnemyNumber() const;

    void SetName(const std::string& value);
    const std::string& GetName() const;

private:
    Fraction(FractionClass* c);

    std::string m_name;

    friend class FractionClass;
};

class FractionPart : public Relation
{

};

class FractionProperty : public Relation
{

};

class FractionUnion : public Relation
{

};

class FractionEnemy : public Relation
{

};

class FractionLeader : public Relation
{

};

class FractionEconomist : public Relation
{

};

class FractionCommanderInChief : public Relation
{

};

Fraction* DeclareFraction(const std::string& name, Human* leader);

bool IsLeader(Human* h);
Human* FindLeader(Fraction* f);
Fraction* FindLeadingFraction(Human* h);
bool HasLeader(Fraction* f);
void AssignLeader(Fraction* f, Human* h);
void ReassignLeader(Fraction* f);

bool HasUnion(Fraction* a, Fraction* b);
void CreateUnion(Fraction* a, Fraction* b);
void DestroyUnion(Fraction* a, Fraction* b);
const std::map<std::string, Fraction*> FindAllAllies(Fraction* f);

bool HasWar(Fraction* a, Fraction* b);
void CreateWar(Fraction* a, Fraction* b);
void DestroyWar(Fraction* a, Fraction* b);
const std::map<std::string, Fraction*> FindAllEnemies(Fraction* f);


#endif // FRACTION_H

#endif //   USE_STATE
