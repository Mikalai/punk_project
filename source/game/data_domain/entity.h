#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <set>
#include <memory>

class Relation;
class Attribute;

class EntityClass;

class Entity
{
public:
    Entity(EntityClass* e);
    virtual ~Entity();

    void AddRelation(Relation* value);
    void RemoveRelation(Relation* value);

    std::set<Relation*>& GetRelations();
    const std::set<Relation*>& GetRelations() const;

    const EntityClass* GetClass() const;
    EntityClass* GetClass();

    void AddAttribute(Attribute* attribute);

    std::set<Attribute*>& GetAttributeArray();
    const std::set<Attribute*>& GetAttributeArray() const;

private:

    EntityClass* m_class;
    std::set<Relation*> m_relations;
    std::set<Attribute*> m_attributes;
};


#endif // ENTITY_H
