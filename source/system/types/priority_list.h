#ifndef _H_PUNK_SYSTEM_PRIORITY_LIST
#define _H_PUNK_SYSTEM_PRIORITY_LIST

#define USE_STL_LIST
#ifdef USE_STL_LIST

#include <iostream>
#include <algorithm>
#include <list>

namespace System
{
	template<typename T, typename Cmp = std::less<T> >
	class priority_list
	{	
	private:
		typedef std::list<T> container;

	public:
		typedef typename container::iterator iterator;
		typedef typename container::const_iterator const_iterator;

	private:
		container m_list;
		Cmp m_cmp;

		template<class T>
		struct Find
		{
			T& m_e;
			Cmp& m_cmp;
			Find(T& e, Cmp& cmp) : m_e(e), m_cmp(cmp) {}

			bool operator () (T& e)
			{
				return m_cmp(m_e, e);
			}
		};

	public:

		inline void push(T e)
		{
			iterator it = std::find_if(m_list.begin(), m_list.end(), Find<T>(e, m_cmp));
			m_list.insert(it, e);
		}

		void insert_if(T e, Cmp& cmp)
		{
			struct Find
			{
				T& m_e;
				Cmp& m_cmp;
				Find(T& e, Cmp& cmp) : m_e(e), m_cmp(cmp) {}

				bool operator () (T& e)
				{
					return m_cmp(m_e, e);
				}
			};

			iterator it = std::find_if(m_list.begin(), m_list.end(), Find(e, cmp));
			m_list.insert(it, e);
		}

		void adjust_position(T t)
		{
			container::iterator it = std::find(m_list.begin(), m_list.end(), t);
			if (it == m_list.end())
			{			
				std::cout << "Can't adjust position. No element found. " << std::endl;
				return;
			}
			m_list.erase(it);
			push(t);
		}

		T top()
		{
			return m_list.front();
		}

		void pop()
		{
			m_list.pop_front();
		}

		bool empty()
		{
			return m_list.empty();
		}

		int size()
		{
			return m_list.size();
		}

		iterator begin()
		{
			return m_list.begin();
		}

		const_iterator begin() const
		{
			return m_list.begin();
		}

		iterator end()
		{
			return m_list.end();
		}

		const_iterator end() const
		{
			return m_list.end();
		}

		void clear()
		{
			m_list.clear();
		}
	};

#endif	//	USE_STD_LIST

#ifdef USE_OWN_LIST
	template<class T>
	class Allocator
	{
		static T* Alloc()
		{
			return new T();
		}

		void Free(T* v)
		{
			delete v;
		}
	};

	template<class T, class compare, class alloc = Allocator<T> >
	class PriorityList
	{
	public:

		struct Node
		{
			T m_data;
			Node* m_next;
			Node* m_prev;

			void Insert(Node* new_node)
			{
				if (compare(new_node->m_data, m_data))
				{
					if (m_next != &m_end)
						m_next->Insert(new_node);
					else
					{
						m_next = new_node;
						new_node->m_next = &m_end;
					}
				}
				else
				{
					new_node->m_next = this;
					new_node->m_prev = m_prev;
					m_prev = new_node;
				}
			}

			static Node m_end;
		};

		void push(T value)
		{
			Node* node = alloc::Alloc<Node>();
			node->m_data = value;

			if (m_head)
				m_head->Insert(node);
			else
			{
				m_head = node;
				m_head->m_next = &m_end;
			}
		}

		T pop()
		{
			if (m_head)
			{
				Node* pop_node = m_head;
				m_head = m_head->m_next;
				T result = pop_node->m_data;
				alloc::Free<Node>(pop_node);
				return result;
			}
			else
			{
				return T();
			}
		}

		Node* begin()
		{
			return m_head;
		}

		Node* m_head;	
	};
#endif	//	USE_OWN_LIST
}

#endif	//	_H_PUNK_SYSTEM_PRIORITY_LIST