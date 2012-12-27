#include "logger.h"
#include "compound_object.h"
#include "factory.h"

namespace System
{
	bool CompoundObject::Save(std::ostream& stream) const
	{
		if (!Object::Save(stream))
			return (out_error() << "Can't save compound object" << std::endl, false);

		unsigned total_count = m_children.size();
		stream.write((char*)&total_count, sizeof(total_count));

		for each (const auto& o in m_children)
		{
			System::GetFactory()->SaveToStream(stream, o);
		}

		return true;
	}

	bool CompoundObject::Load(std::istream& stream)
	{
		if (!Object::Load(stream))
			return (out_error() << "Can't load compound object" << std::endl, false);

		unsigned total_count = 0;
		stream.read((char*)&total_count, sizeof(total_count));

		for (int i = 0; i < (int)total_count; ++i)
		{
			Proxy<Object> o = GetFactory()->LoadFromStream(stream);
			if (!o.IsValid())
				return (out_error() << "Can't load compound object" << std::endl, false);
			if (!Add(o))
				return (out_error() << "Can't add loaded object to the object list" << std::endl, false);
		}

		return true;
	}

	bool CompoundObject::Add(Proxy<Object> value)
	{
		if (value == nullptr)
			return (out_error() << "Can't add null object" << std::endl, false);

		auto it = m_cache.find(value->GetStorageName());

		if (it != m_cache.end())
			out_warning() << "Object with name " << value->GetStorageName() << " already in the set" << std::endl;

		m_children.push_back(value);
		m_cache[value->GetStorageName()] = m_children.size() - 1;

		if (!OnAdd(value))
			return (out_error() << "OnAdd failed" << std::endl, false);

		return true;
	}

	bool CompoundObject::Remove(Proxy<Object> value)
	{
		if (value == nullptr)
			return (out_error() << "Can't remove null object" << std::endl, false);

		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (it->Get() == value.Get())
			{
				m_children.erase(it);
				m_cache.erase(m_cache.find(value->GetStorageName()));
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
		auto it = m_cache.find(name);
		if (it == m_cache.end())
			return (out_warning() << "Can't remove object " << name << std::endl, false);

		if  (!OnRemove(m_children[it->second]))
			return (out_error() << "OnRemove failed" << std::endl, false);

		m_children.erase(m_children.begin() + it->second);	
		m_cache.erase(it);
		return true;
	}

	bool CompoundObject::Remove(int index)
	{
		try
		{
			auto storage_name = m_children.at(index)->GetStorageName();
			if (!OnRemove(m_children[index]))
				return (out_error() << "OnRemove failed" << std::endl, false);
			m_cache.erase(m_cache.find(storage_name));
			m_children.erase(m_children.begin() + index);
		}
		catch(...)
		{
			out_error() << "Can't remove object with " << index << " index" << std::endl, false;
		}
		return true;
	}

	const Proxy<Object> CompoundObject::Find(const string& name) const
	{
		auto it = m_cache.find(name);
		if (it == m_cache.end())
			return Proxy<Object>(nullptr);
		return m_children[it->second];
	}

	const Proxy<Object> CompoundObject::Find(int index) const
	{
		return m_children[index];
	}

	Proxy<Object> CompoundObject::Find(const string& name)
	{
		return static_cast<const CompoundObject*>(this)->Find(name);
	}

	Proxy<Object> CompoundObject::Find(int index)
	{
		return static_cast<const CompoundObject*>(this)->Find(index);
	}
}