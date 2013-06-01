#include "property.h"

namespace Common
{

Property::Property()
{
}

bool DoOwn(Entity *owner, Entity *item)
{
    auto property = Find<Property>(owner);
    for (auto p : property)
    {
        if (p->GetB() == item)
            return true;
    }
    return false;
}

bool HasOwner(Entity *item)
{
    auto property = Find<Property>(item);
    return !property.empty();
}

Entity* FindOwner(Entity *item)
{
    if (HasOwner(item))
        throw LocalsException(ERROR_ENTITY_HAS_GOT_NO_OWNER);

    auto property = Find<Property>(item);
    return property[0]->GetA();
}

void Take(Entity *owner, Entity *item)
{
    if (HasOwner(item))
        return;
    std::auto_ptr<Property> p(new Property);
    p->SetA(owner);
    p->SetB(item);
    owner->AddRelation(p.get());
    item->AddRelation(p.get());
    p.release();
}

void Drop(Entity *owner, Entity *item)
{
    if (!HasOwner(item))
        return;
    if (owner != FindOwner(item))
        return;
    auto property = Find<Property>(owner);
    item->RemoveRelation(property[0]);
    owner->RemoveRelation(property[0]);
    delete property[0];
}

void Steal(Entity *owner, Entity *item)
{
    if (HasOwner(item))
    {
        auto prev_owner = FindOwner(item);
        Drop(prev_owner, item);
    }
    Take(owner, item);
}

std::vector<Entity*> FindProperty(Entity *owner)
{
    std::vector<Entity*> result;
    auto property = Find<Property>(owner);
    for (auto p : property)
    {
        result.push_back(p->GetB());
    }
    return result;
}

}
