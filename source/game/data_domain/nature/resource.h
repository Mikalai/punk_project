#ifdef USE_NATURE

#ifndef RESOURCE_H
#define RESOURCE_H

#include "era.h"

class ResourceClass : public EntityClass
{
public:

};

class Resource : public Entity
{
public:
    Resource(ResourceClass* c);
};

#endif // RESOURCE_H

#endif//    #ifdef USE_NATURE
