#ifdef USE_STATE

#include <iostream>
#include <algorithm>
#include "fraction.h"
#include "era.h"
#include "human.h"

FractionClass g_fraction_class("Neutral");

std::vector<Fraction*> FractionClass::m_all_fractions;

Fraction* FractionClass::Create(const std::string &name)
{
    Fraction* f(new Fraction(this));
    f->SetName(name);
    Register(f);
    return f;
}

void FractionClass::Destroy(Entity *value)
{
    Unregister(value);
    delete value;
}

void FractionClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_fractions.begin(), m_all_fractions.end(), dynamic_cast<Fraction*>(value));
    if (it != m_all_fractions.end())
        m_all_fractions.erase(it);

    EntityClass::Unregister(value);
}

void FractionClass::Register(Entity *value)
{
    m_all_fractions.push_back(dynamic_cast<Fraction*>(value));
    EntityClass::Register(value);
}



Fraction::Fraction(FractionClass* c)
    : Entity(c)
{
}

void Fraction::SetName(const std::string &value)
{
    m_name = value;
}

Fraction* DeclareFraction(const std::string &name, Human *leader)
{
    Fraction* f = g_fraction_class.Create(name);
    AssignLeader(f, leader);
    return f;
}

bool IsLeader(Human* h)
{
    auto leader_relations = Find<FractionLeader>(h);
    return !leader_relations.empty();
}

Human* FindLeader(Fraction* f)
{
    if (!HasLeader(f))
        throw LocalsException(ERROR_FRACTION_HAS_GOT_NO_LEADER);

    auto leader_relation = Find<FractionLeader>(f)[0];

    return dynamic_cast<Human*>((leader_relation->GetA() == f) ? leader_relation->GetB() : leader_relation->GetA());
}

bool HasLeader(Fraction *f)
{
    auto leader_relation = Find<FractionLeader>(f);
    return !leader_relation.empty();
}

Fraction* FindLeadingFraction(Human* h)
{
    if (!IsLeader(h))
        throw LocalsException(ERROR_FRACTION_HUMAN_IS_NOT_LEADER);

    auto leader_relation = Find<FractionLeader>(h)[0];

    return dynamic_cast<Fraction*>(leader_relation->GetA() == h ? leader_relation->GetB() : leader_relation->GetB());
}

void AssignLeader(Fraction *f, Human *h)
{
    if (HasLeader(f))
        throw LocalsException(ERROR_FRACTION_ALREADY_HAS_A_LEADER);

    FractionLeader* leader_relation = new FractionLeader;
    leader_relation->SetA(f);
    leader_relation->SetB(h);
    f->AddRelation(leader_relation);
    h->AddRelation(leader_relation);
}

void ReassignLeader(Fraction *f)
{
    auto leader_relation = Find<FractionLeader>(f);
    if (leader_relation.empty())
        throw LocalsException(ERROR_FRACTION_HAS_GOT_NO_LEADER);
    Entity* leader = leader_relation[0]->GetB();

    f->RemoveRelation(leader_relation[0]);
    leader->RemoveRelation(leader_relation[0]);

    delete leader_relation[0];
}

void CreateUnion(Fraction* a, Fraction* b)
{
    if (HasUnion(a, b))
        throw LocalsException(ERROR_FRACTION_ALREADY_HAS_A_UNION);

    FractionUnion* union_relation = new FractionUnion;
    union_relation->SetA(a);
    union_relation->SetB(b);
    a->AddRelation(union_relation);
    b->AddRelation(union_relation);
}

bool HasUnion(Fraction *a, Fraction *b)
{
    auto union_relations = Find<FractionUnion>(a);
    for (auto u : union_relations)
    {
        if ((u->GetA() == a && u->GetB() == b)
                || (u->GetB() == a && u->GetA() == b))
            return true;
    }
    return false;
}

void DestroyUnion(Fraction* a, Fraction* b)
{
    if (!HasUnion(a, b))
        throw LocalsException(ERROR_FRACTION_HAS_GOT_NO_UNION);

    FractionUnion* relation_union = nullptr;
    auto unions = Find<FractionUnion>(a);
    for (auto u : unions)
    {
        if ( (u->GetA() == a && u->GetB() == b)
                || (u->GetB() == a && u->GetA() == b))
        {
            relation_union = u;
            break;
        }
    }

    a->RemoveRelation(relation_union);
    b->RemoveRelation(relation_union);
    delete relation_union;
}

const std::map<std::string, Fraction*> FindAllAllies(Fraction *f)
{
    auto allies = Find<FractionUnion>(f);
    std::map<std::string, Fraction*> result;
    for (auto u : allies)
    {
        Fraction* fraction = dynamic_cast<Fraction*>((u->GetA() == f) ? u->GetB() : u->GetA());
        result[fraction->GetName()] = fraction;
    }
    return result;
}

bool HasWar(Fraction* a, Fraction* b)
{
    auto war_relations = Find<FractionEnemy>(a);
    for (auto enemy_relation : war_relations)
    {
        if ((enemy_relation->GetA() == a && enemy_relation->GetB() == b)
                || (enemy_relation->GetB() == a && enemy_relation->GetA() == b))
        {
            return true;
        }
    }
    return false;
}

void CreateWar(Fraction* a, Fraction* b)
{
    FractionEnemy* enemy_relation = new FractionEnemy;
    enemy_relation->SetA(a);
}

const std::string& Fraction::GetName() const
{
    return m_name;
}

void FractionClass::PrintAll()
{
    for (auto f : m_all_fractions)
    {
        std::cout << "Fraction: " << f->GetName() << std::endl;
        if (HasLeader(f))
        {
            Human* leader = FindLeader(f);
            std::cout << "Leader: " << leader->GetName() << std::endl;
        }
        else
        {
            std::cout << "No leader" << std::endl;
        }
    }
}

void DestroyWar(Fraction* a, Fraction* b);
const std::map<std::string, Fraction*> FindAllEnemies(const Fraction* f);

#endif  //  USE_STATE
