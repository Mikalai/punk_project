#ifndef PUNK_SYSTEM_RTTI_H
#define PUNK_SYSTEM_RTTI_H

#include "../config.h"
#include "../string/string.h"

namespace System
{
    class Buffer;
    class Object;

    class PUNK_ENGINE_API Rtti
    {
    public:
        Rtti(const string& name, unsigned uid, const Rtti* parent);
        ~Rtti();
        const string& GetName() const;
        unsigned GetId() const;
        const Rtti* GetParent() const;
        bool IsEqual(const Rtti* value) const;
        bool IsDerived(const Rtti* value) const;
        const string ToString() const;
    private:        
        string m_name;
        const Rtti* m_parent;
        unsigned m_id;        
    };
}

#endif // PUNK_SYSTEM_RTTI_H
