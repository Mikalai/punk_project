#include "handle_win32.h"

namespace System
{

	Descriptor::Descriptor(unsigned __int64 code) throw()
	{
		m_id = code;
	}

	Descriptor::Descriptor(unsigned type, unsigned number) throw()
	{
		m_object_type_code = type;
		m_object_instance_number = number;
	}

	Descriptor::Descriptor(const Descriptor &handler) throw() : m_id(handler.m_id)
	{}

	Descriptor& Descriptor::operator = (const Descriptor& handler) throw()
	{
		if (this != &handler)
		{
			m_id = handler.m_id;
		}
		return *this;
	}

	Descriptor::operator unsigned __int64 () const
	{
		return m_id;
	}

	unsigned Descriptor::Type() const
	{
		return m_object_type_code;
	}

	unsigned Descriptor::Number() const
	{
		return m_object_instance_number;
	}

	unsigned __int64 Descriptor::Id() const
	{
		return m_id;
	}

	void Descriptor::SetType(unsigned type)
	{
		m_object_type_code = type;
	}

	void Descriptor::SetNumber(unsigned number)
	{
		m_object_instance_number = number;
	}

	void Descriptor::SetID(unsigned __int64 id)
	{
		m_id = id;
	}

	bool Descriptor::operator == (const Descriptor& handler) const
	{
		return m_id == handler.m_id;
	}

}