#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

namespace System
{
	template<typename T, unsigned Size>
	class array
	{
	protected:
		T m_item[Size];
	public:
		array()
		{
			memset(m_item, 0, sizeof(T)*Size);
		}

		array(const array<T, Size>& a)
		{
			memcpy(m_item, a.m_item, sizeof(T)*Size);
		}

		array<T, Size>& operator = (const array<T, Size>& a)
		{
			if (&a != this)
			{
				memcpy(m_item, a.m_item, sizeof(T)*Size);
			}
			return *this;
		}

		T& operator [] (int index)
		{
			return m_item[index];
		}

		const T& operator [] (int index) const
		{
			return m_item[index];
		}

		int Size() const
		{
			return Size;
		}
	};
}
#endif // ARRAY_H_INCLUDED
