#ifndef _H_PUNK_DYNAMIC_ARRAY
#define _H_PUNK_DYNAMIC_ARRAY

namespace System
{
	template<class T, int Step = 10>
	class DynamicArray
	{
		struct Rep
		{
			unsigned m_usage;
			unsigned m_max_size;
			unsigned m_size;
			T* m_items;

			Rep() : m_usage(1), m_max_size(Step), m_size(0), m_items(new T[m_max_size]);
			{}

			Rep(int max_size) : m_usage(1), m_max_size(max_size), m_size(0), m_items(new T[m_max_size])
			{}

			Rep(const Rep& rep)
			{}

			~Rep()
			{
				if (m_items)
				{
					delete[] m_items;
					m_items = 0;
				}
			}

			Rep* GetOwnCopy()
			{
				if (m_usage == 1)
					return this;
				else
				{
					m_usage--;
					Rep* rep = new Rep(m_max_size);
					rep->m_size = m_size;
					memcpy(rep->m_items, m_items, sizeof(T)*m_max_size);
					return rep;
				}
			}

			void Resize(int max_size)
			{
				if (max_size <= m_max_size)
				{
					m_max_size = max_size;
					return;
				}

				T* tmp = new T[m_max_size];
				memcpy(tmp, m_items, sizeof(T)*m_max_size);
				delete[] m_items;
				m_items = new T[m_max_size + Step];
				memcpy(m_items, tmp, sizeof(m_max_size));
				delete[] tmp;
				m_max_size += Step;
			}

			void Push(T e)
			{
				if (m_size == m_max_size)
					Resize(m_max_size + Step)
				m_items[m_size++] = e;
			}

			T Pop()
			{
				if (m_size > 0)
					return m_items[--m_size];
				return T();
			}

		};

		Rep* m_rep;

	public:
		DynamicArray() : m_rep(new Rep()) {}
		DynamicArray(int max_size) : m_rep(new Rep(max_size)) {}

		DynamicArray<T>& operator = (const DynamicArray<T>& arr)
		{
			if (this != &arr)
			{
				m_rep = arr.m_rep;
				m_rep->m_usage++;
			}
		}

		T& operator [] (int index)
		{
			m_rep = m_rep->GetOwnCopy();
			return m_rep->m_items[index];
		}

		const T& operator [] (int index) const
		{
			return m_rep->m_items[index];
		}

		void Push(T e)
		{
			m_rep = m_rep->GetOwnCopy();
			m_rep->Push(e);
		}

		T Pop()
		{
			m_rep = m_rep->GetOwnCopy();
			return m_rep->Pop()
		}

		~DynamicArray()
		{
			if (--m_rep->m_usage == 0)
			{
				delete m_rep;
				m_rep = 0;
			}
		}
	};
}

#endif