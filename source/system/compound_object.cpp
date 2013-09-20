#include <algorithm>
#include "logger.h"
#include "compound_object.h"
#include "factory.h"
#include "../engine_objects.h"

namespace System
{
    StaticInormation<CompoundObject> CompoundObject::Info{"System.CompoundObject", PUNK_COMPOUND_OBJECT, &Object::Info.Type};

    CompoundObject::CompoundObject()
    {
        Info.Add(this);
    }

    CompoundObject::~CompoundObject()
    {
        for (auto it = m_children.begin(); it != m_children.end(); ++it)
            safe_delete(*it);
        m_children.clear();
        Info.Remove(this);
    }

    bool CompoundObject::Add(Object* value)
    {
        if (value == nullptr)
            return (out_error() << "Can't add null object" << std::endl, false);

        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it != m_children.end())
            return true;

        m_children.push_back(value);
        value->SetOwner(this);

        if (!OnAdd(value))
            return (out_error() << "OnAdd failed" << std::endl, false);

        return true;
    }

    bool CompoundObject::Remove(Object* value, bool depth)
    {
        if (value == nullptr)
            return false;

        for (auto it = m_children.begin(); it != m_children.end(); ++it)
        {
            if (*it == value)
            {
                m_children.erase(it);
                value->SetOwner(nullptr);
                return true;
            }
        }

        if (depth)
        {
            for (auto o : m_children)
            {
                CompoundObject* co = As<CompoundObject*>(o);
                if (co)
                {
                    if (co->Remove(value, depth))
                        return true;
                }
            }
        }
        return false;
    }

    bool CompoundObject::Remove(int index)
    {
        if (index < 0 || index >= m_children.size())
            return false;
        return Remove(m_children[index]);
    }


    const Object* CompoundObject::Find(int index) const
    {
        return m_children[index];
    }

    Object* CompoundObject::Find(int index)
    {
        return const_cast<Object*>(static_cast<const CompoundObject*>(this)->Find(index));
    }


    void Bind(CompoundObject* parent, Object* child)
    {
        CompoundObject* owner = As<CompoundObject*>(child->GetOwner());
        if (owner)
            owner->Remove(child);
        parent->Add(child);
        child->SetOwner(parent);
    }

    const string CompoundObject::ToString() const
    {
        std::wstringstream stream;
        stream << '[' << GetLocalIndex() << ' ' << Info.Type.GetName() << ']' << std::endl;
        for (auto o : m_children)
        {
            stream << o->ToString() << std::endl;
        }
        return string(stream.str());
    }

    void CompoundObject::Save(Buffer* buffer) const
    {
        Object::Save(buffer);
        unsigned count = m_children.size();
        buffer->WriteUnsigned32(count);
        for (auto child : m_children)
        {
            child->Save(buffer);
        }
    }

    void CompoundObject::Load(Buffer* buffer)
    {
        Object::Load(buffer);
        unsigned count{buffer->ReadUnsigned32()};
        for (auto i = 0; i != count; ++i)
        {
            unsigned code = buffer->ReadUnsigned32();
            Object* object{Factory::Create(code)};
            object->Load(buffer);
            Add(object);
        }
    }
}
