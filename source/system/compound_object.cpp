#include "logger.h"
#include "compound_object.h"
#include "factory.h"

namespace System
{
	CompoundObject::~CompoundObject()
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
			safe_delete(*it);
		m_children.clear();		
	}

	bool CompoundObject::Save(std::ostream& stream) const
	{
		if (!Object::Save(stream))
			return (out_error() << "Can't save compound object" << std::endl, false);

		unsigned total_count = m_children.size();
		stream.write((char*)&total_count, sizeof(total_count));

		for (const auto& o : m_children)
		{
			System::GetFactory()->SaveToStream(stream, o);
		}

		return true;
	}

	bool CompoundObject::Load(std::istream& stream)
	{
		Object::Load(stream);


		unsigned total_count = 0;
		stream.read((char*)&total_count, sizeof(total_count));

		for (int i = 0; i < (int)total_count; ++i)
		{
			Object* o = GetFactory()->LoadFromStream(stream);
			if (!o)
				throw PunkInvalidArgumentException(L"Can't load compound object");
			if (!Add(o))
				return (out_error() << "Can't add loaded object to the object list" << std::endl, false);
		}

		return true;
	}

	bool CompoundObject::Add(Object* value)
	{
		if (value == nullptr)
			return (out_error() << "Can't add null object" << std::endl, false);

        auto o = Find(value->GetName());

        if (o)
            out_warning() << "Object with name " << value->GetName() << " already in the set" << std::endl;

		m_children.push_back(value);
        value->SetOwner(this);

		if (!OnAdd(value))
			return (out_error() << "OnAdd failed" << std::endl, false);

		return true;
	}

	bool CompoundObject::Remove(Object* value)
	{
		if (value == nullptr)
			return (out_error() << "Can't remove null object" << std::endl, false);

		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it == value)
			{
				m_children.erase(it);
                value->SetOwner(nullptr);
				return true;
			}
		}

		out_warning() << "Object " << value->GetStorageName() << " was not found" << std::endl;

		if (!OnRemove(value))
			return (out_error() << "OnRemove failed" << std::endl, false);

		return false;
	}

	bool CompoundObject::Remove(const string& name)
	{        
        return Remove(Find(name));
	}

	bool CompoundObject::Remove(int index)
	{
        if (index < 0 || index >= m_children.size())
            return false;
        return Remove(m_children[index]);
	}

    const Object* CompoundObject::Find(const string& name, bool in_depth) const
	{
        for (Object* o : m_children)
        {
            if (o->GetName() == name)
                return o;
        }
        if (in_depth)
        {
            for (Object* o : m_children)
            {
                CompoundObject* co = As<CompoundObject*>(o);
                if (co)
                {
                    Object* res = co->Find(name, in_depth);
                    if (res)
                        return res;
                }
            }
        }
        return nullptr;
	}

    size_t CompoundObject::GetIndex(const System::string& name) const
    {
        size_t index = 0;
        for (const Object* o : m_children)
        {
            if (o->GetName() == name)
                return index;
            index++;
        }
        return -1;
    }

    const Object* CompoundObject::Find(int index) const
	{
		return m_children[index];
	}

    Object* CompoundObject::Find(const string& name, bool in_depth)
	{
        return const_cast<Object*>(static_cast<const CompoundObject*>(this)->Find(name, in_depth));
	}

    Object* CompoundObject::Find(int index)
	{
        return const_cast<Object*>(static_cast<const CompoundObject*>(this)->Find(index));
	}
}
