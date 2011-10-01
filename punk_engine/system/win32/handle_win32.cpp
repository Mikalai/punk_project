#include "handle_win32.h"

namespace System
{

	Handle::Handle(unsigned __int64 code) throw()
	{
		m_id = code;
	}

	Handle::Handle(unsigned type, unsigned number) throw()
	{
		m_object_type_code = type;
		m_object_instance_number = number;
	}

	Handle::Handle(const Handle &handler) throw() : m_id(handler.m_id)
	{}

	Handle& Handle::operator = (const Handle& handler) throw()
	{
		if (this != &handler)
		{
			m_id = handler.m_id;
		}
		return *this;
	}

	Handle::operator unsigned __int64 () const
	{
		return m_id;
	}

	unsigned Handle::Type() const
	{
		return m_object_type_code;
	}

	unsigned Handle::Number() const
	{
		return m_object_instance_number;
	}

	unsigned __int64 Handle::Id() const
	{
		return m_id;
	}

	void Handle::SetType(unsigned type)
	{
		m_object_type_code = type;
	}

	void Handle::SetNumber(unsigned number)
	{
		m_object_instance_number = number;
	}

	void Handle::SetID(unsigned __int64 id)
	{
		m_id = id;
	}

	bool Handle::operator == (const Handle& handler) const
	{
		return m_id == handler.m_id;
	}

}