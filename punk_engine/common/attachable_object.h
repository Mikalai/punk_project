#ifndef ATTACHABLE_OBJECT_H
#define ATTACHABLE_OBJECT_H

#include "simple_container.h"

namespace Common
{
    class AttachableObject
    {
        const AttachableObject* parent;
        SimpleContainer<AttachableObject*> child;
    public:
        AttachableObject();
        AttachableObject(const AttachableObject&);
        AttachableObject* GetParent() const;
        SimpleContainer<AttachableObject*>& GetChildren() const;
        void Attach(AttachableObject* value);
        void Detach();
        bool IsAttached() const;
        bool HasAttachedObjects() const;
    };
}

#endif // ATTACHABLE_OBJECT_H
