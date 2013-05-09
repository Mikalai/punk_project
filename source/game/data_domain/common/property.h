#ifndef PROPERTY_H
#define PROPERTY_H

#include "../era.h"

namespace Common
{

//  a - owner
//  b - subject
class Property : public Relation
{
public:
    Property();
};

bool DoOwn(Entity* owner, Entity* item);
bool HasOwner(Entity* item);
void Take(Entity* owner, Entity* item);
void Steal(Entity* owner, Entity* item);
void Drop(Entity* owner, Entity* item);
Entity* FindOwner(Entity* item);
std::vector<Entity*> FindProperty(Entity* owner);

}

#endif // PROPERTY_H
