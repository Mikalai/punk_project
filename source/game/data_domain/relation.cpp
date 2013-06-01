#include "relation.h"
#include "entity.h"

Relation::Relation()
    : m_a(nullptr)
    , m_b(nullptr)
    , m_power(1)
{
}

Relation::~Relation()
{}

void Relation::SetA(Entity *value)
{
    m_a = value;
}

void Relation::SetB(Entity *value)
{
    m_b = value;
}

Entity* Relation::GetA()
{
    return m_a;
}

const Entity* Relation::GetA() const
{
    return m_a;
}

Entity* Relation::GetB()
{
    return m_b;
}

const Entity* Relation::GetB() const
{
    return m_b;
}
