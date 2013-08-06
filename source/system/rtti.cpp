#include "rtti.h"
#include "../string/string.h"
#include <sstream>

namespace System
{

    Rtti::Rtti(const string &name, unsigned uid, const Rtti *parent)
        : m_name(name)
        , m_parent(parent)
        , m_id(uid)
    {        
    }

    Rtti::~Rtti()
    {}

    const string& Rtti::GetName() const
    {
        return m_name;
    }

    unsigned Rtti::GetId() const
    {
        return m_id;
    }

    const Rtti* Rtti::GetParent() const
    {
        return m_parent;
    }

    bool Rtti::IsEqual(const Rtti* value) const
    {
        return this == value;
    }

    bool Rtti::IsDerived(const Rtti* value) const
    {
        const Rtti* cur = this;
        while (cur)
        {
            if (value == cur)
                return true;
            cur = cur->GetParent();
        }
        return false;
    }

    const string Rtti::ToString() const
    {
        std::wstringstream stream;
        stream << L'[' << m_name << L" (" << m_id << L")";
        if (m_parent)
            stream << L" -> " << m_parent->ToString() << L']';
        else
            stream << L']';
        return string(stream.str());
    }
}
