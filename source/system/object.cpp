#include <sstream>
#include "buffer.h"
#include "object.h"
#include "../engine_objects.h"

namespace System
{
    StaticInormation<Object> Object::Info{"System.Object", PUNK_OBJECT, SaveObject, LoadObject, 0};
    unsigned Object::m_id_next= 0;

    Object::Object()
        : m_owner{nullptr}
        , m_id(m_id_next++)
    {
        Info.Add(this);
    }

    Object::~Object()
    {
        Info.Remove(this);
    }

    void Object::SetOwner(Object* owner)
    {
        m_owner = owner;
    }

    const Object* Object::GetOwner() const
    {
        return m_owner;
    }

    Object* Object::GetOwner()
    {
        return m_owner;
    }  

    const string Object::ToString() const
    {
        std::wstringstream stream;
        stream << '[' << GetLocalIndex() << ' ' << Info.Type.GetName() << ']';
        return string(stream.str());
    }

    unsigned Object::GetId() const
    {
        return m_id;
    }

    const string& Object::Name() const
    {
        return m_name;
    }

    void Object::Name(const string& value)
    {
        m_name = value;
    }


    void SaveObject(Buffer *buffer, const Object *o)
    {
        /*
         *  We write type code, as a tag for factory, that should be able
         *  to create an object from code. It will not be read from Load.
         */
        auto id = o->Info.Type.GetId();
        buffer->WriteUnsigned32(id);
    }

    void LoadObject(Buffer *buffer, Object *o)
    {}
}
