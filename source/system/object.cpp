#include <ostream>
#include <istream>
#include "object.h"

namespace System
{
    Object::Object()
        : m_modified(false)
        , m_owner(nullptr)
    {}

    Object::~Object()
    {}

    void Object::SetName(const string& value)
    {
        m_name = value;
    }

    const string& Object::GetName() const
    {
        return m_name;
    }

    void Object::SetText(const string& value)
    {
        m_text = value;
    }

    const string& Object::GetText() const
    {
        return m_text;
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

    const System::string& Object::GetStorageName() const
    {
        return m_storage_name;
    }

    void Object::SetStorageName(const System::string& name)
    {
        m_storage_name = name;
    }

    ObjectType Object::GetType() const
    {
        return m_type;
    }

    void Object::SetType(ObjectType type)
    {
        m_type = type;
    }

    bool Object::IsModified() const
    {
        return m_modified;
    }

    void Object::Invalidate()
    {
        m_modified = true;
    }

	bool Object::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_modified, sizeof(m_modified));
		stream.write((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object storage name");
		if (!m_name.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object name");
		if (!m_text.Save(stream))
			throw PunkInvalidArgumentException(L"Can't save object text");
		return true;
	}

	bool Object::Load(std::istream& stream)
	{
		stream.read((char*)&m_modified, sizeof(m_modified));
		stream.read((char*)&m_type, sizeof(m_type));

		if (!m_storage_name.Load(stream))
			throw PunkInvalidArgumentException(L"Can't load object storage name");
		if (!m_name.Load(stream))
			throw PunkInvalidArgumentException(L"Can't save object name");
		if (!m_text.Load(stream))
			throw PunkInvalidArgumentException(L"Can't save object text");
		return true;
	}
}
