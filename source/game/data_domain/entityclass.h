#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include <set>
#include <vector>
#include <string>
class Entity;

class EntityClass
{
public:

    EntityClass(const std::string& name);

    const std::string GetName() const { return m_name; }

    virtual void Destroy(Entity* value) = 0;

    virtual void Register(Entity* e);
    virtual void Unregister(Entity* e);

private:
    std::string m_name;
    static std::vector<Entity*> m_all_entities;
};

#endif // ENTITYCLASS_H
