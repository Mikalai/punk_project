#include <iostream>
#include <memory>

#include "property.h"

namespace Logic
{
	Property::Property() : m_string(0)
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		m_type = Type::TYPE_INTEGER;
		m_int = 0;
	}

	Property::Property(ID name) : m_string(0)
		, m_name(name)
	{	
		//	std::cout << __FUNCSIG__ << std::endl;
		m_type = Type::TYPE_INTEGER;
		m_int = 0;
	}

	Property::Property(const Property& p) : m_string(0)
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		m_name = p.m_name;
		m_type = p.m_type;
		switch(m_type)
		{
		case Type::TYPE_INTEGER:
			m_int = p.m_int;
			break;
		case Type::TYPE_REAL:
			m_real = p.m_real;
			break;
		case Type::TYPE_STRING:
			{
				int size = (wcslen(p.m_string)+1)*sizeof(wchar_t);
				Allocate(size);
				memcpy_s(m_string, size, p.m_string, size);			
			}
			break;
		}
	}

	Property::~Property()
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		Deallocate();
	}

	Property& Property::operator = (const Property& p)
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		if (this != &p)
		{		
			m_name = p.m_name;		
			switch(p.m_type)
			{
			case Type::TYPE_INTEGER:
				Deallocate();
				m_type = p.m_type;
				m_int = p.m_int;
				break;
			case Type::TYPE_REAL:
				Deallocate();
				m_type = p.m_type;
				m_real = p.m_real;
				break;
			case Type::TYPE_STRING:
				{
					int size = (wcslen(p.m_string)+1)*sizeof(wchar_t);
					Allocate(size);
					memcpy_s(m_string, size, p.m_string, size);		
				}
				break;
			}
		}
		return *this;
	}

	bool Property::IsProperty(ID name)
	{
		return m_name == name;
	}

	ID Property::GetName() const
	{
		return m_name;
	}

	void Property::SetName(ID name)
	{
		m_name = name;
	}

	void Property::SetValue(int value)
	{
		Deallocate();
		m_type = Type::TYPE_INTEGER;
		m_int = value;
	}

	void Property::SetValue(double value)
	{
		Deallocate();
		m_type = Type::TYPE_REAL;
		m_real = value;
	}

	void Property::SetValue(const wchar_t* string)
	{
		m_type = TYPE_STRING;
		int size = (wcslen(string)+1)*sizeof(wchar_t);
		Allocate(size);
		memcpy_s(m_string, size, string, size);	
	}

	int Property::AsInt() const
	{
		return m_int;
	}

	double Property::AsReal() const
	{
		return m_real;
	}

	const wchar_t* Property::AsString() const
	{
		return m_string;
	}

	Property::Type Property::GetType() const
	{
		return m_type;
	}

	void Property::Allocate(int size)
	{
		if (m_string)
		{
			int cur_size = (wcslen(m_string)+1)*sizeof(wchar_t);
			if (cur_size < size)
			{
				delete[] m_string;
				m_string = reinterpret_cast<wchar_t*>(new char[size]);
			}
		}
		else
		{
			m_string = reinterpret_cast<wchar_t*>(new char[size]);
		}
	}

	void Property::Deallocate()
	{
		if (m_type == TYPE_STRING)
		{
			delete[] reinterpret_cast<char*>(m_string);
			m_string = 0;
		}
	}

	void Property::Inc(int value)
	{
		m_int += value;
	}

	void Property::Dec(int value)
	{
		m_int -= value;
	}

	void Property::Inc(double value)
	{
		m_real += value;
	}

	void Property::Dec(double value)
	{
		m_real -= value;
	}
}