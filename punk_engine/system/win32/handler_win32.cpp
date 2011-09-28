#include "handler_win32.h"

namespace System
{

	Handler::Handler(unsigned __int64 code) throw()
	{
		m_id = code;
	}

	Handler::Handler(unsigned type, unsigned number) throw()
	{
		m_object_type_code = type;
		m_object_instance_number = number;
	}

	Handler::Handler(const Handler &handler) throw() : m_id(handler.m_id)
	{}

	Handler& Handler::operator = (const Handler& handler) throw()
	{
		if (this != &handler)
		{
			m_id = m_handler.id;
		}
		return *this;
	}

	Handler::operator unsigned __int64 () const
	{
		return m_id;
	}

	unsigned Handler::Type() const
	{
		return m_object_type_code;
	}

	unsigned Handler::Number() const
	{
		return m_object_instance_number;
	}

	unsigned __int64 Handler::Id() const
	{
		return m_id;
	}

	void Handler::SetType(unsigned type)
	{
		m_object_type_code = type;
	}

	void Handler::SetNumber(unsigned number)
	{
		m_object_instance_number = number;
	}

	void Handler::SetID(unsigned __int64 id)
	{
		m_id = id;
	}

	bool Handler::operator == (const Handler& handler) const
	{
		return m_id == handler.m_id;
	}

}