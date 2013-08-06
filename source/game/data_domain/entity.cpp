#include "entity.h"
#include "relation.h"
#include "attribute.h"

Entity::Entity(EntityClass* c)
    : m_class(c)
{}

Entity::~Entity()
{
    for (auto a : m_attributes)
    {
        delete a;
    }
    m_attributes.clear();
}

void Entity::AddRelation(Relation *value)
{
    m_relations.insert(value);
}

void Entity::RemoveRelation(Relation *value)
{
    m_relations.erase(value);
}

std::set<Relation*>& Entity::GetRelations()
{
    return m_relations;
}

const std::set<Relation*>& Entity::GetRelations() const
{
    return m_relations;
}

const EntityClass* Entity::GetClass() const
{
    return m_class;
}

EntityClass* Entity::GetClass()
{
    return m_class;
}

std::set<Attribute*>& Entity::GetAttributeArray()
{
    return m_attributes;
}

const std::set<Attribute*>& Entity::GetAttributeArray() const
{
    return m_attributes;
}

void Entity::AddAttribute(Attribute *attribute)
{
    m_attributes.insert(attribute);
}
