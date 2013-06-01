#ifndef ER_H
#define ER_H

#include <vector>
#include "local_errors.h"
#include "entity.h"
#include "relation.h"
#include "attribute.h"
#include "entityclass.h"

template<class R>
inline std::vector<R*> Find(Entity* e)
{
    std::vector<R*> result;
    for (auto r : e->GetRelations())
    {
        R* res = dynamic_cast<R*>(r);
        if (res)
        {
            result.push_back(res);
        }
    }
    return result;
}

template<class R>
inline std::vector<const R*> Find(const Entity* e)
{
    std::vector<const R*> result;
    for (auto r : e->GetRelations())
    {
        const R* res = dynamic_cast<const R*>(r);
        if (res)
        {
            result.push_back(res);
        }
    }
    return result;
}

template<class E>
inline E* Find(Relation* r)
{
    E* res = dynamic_cast<E*>(r->GetA());
    if (res)
        return res;
    res = dynamic_cast<E*>(r->GetB());
    if (res)
        return res;
    return nullptr;
}

template<class A>
inline A* GetAttribute(Entity* e)
{
    auto attributes = e->GetAttributeArray();
    for (auto a : attributes)
    {
        A* result = dynamic_cast<A*>(a);
        if (result)
            return result;
    }
    return nullptr;
}

#endif // ER_H
