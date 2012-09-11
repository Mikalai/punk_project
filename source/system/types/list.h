#ifndef _PUNK_SYSTEM_LIST
#define _PUNK_SYSTEM_LIST

#include "../logger.h"
#include "../allocator.h"

namespace System
{
	template<typename T, template<typename U> class Allocator = DefaultAllocator>
	class List
	{
		struct Node
		{
			T m_data;
			Node* m_next;
			Node* m_prev;

		private:

			T operator * ()
			{
				return m_data;
			}

			void InsertAfter(Node* node, Node* end)
			{
#ifdef _DEBUG
				if (!node || node == end)
					out_error() << "Can't insert Null node" << std::endl;
#endif
				node->m_next = m_next;
				m_next = node;
				node->m_prev = this;
			}

			void InsertBefore(Node* node, Node* end)
			{
#ifdef _DEBUG
				if (!node || node == end)
					out_error() << "Can't insert Null node" << std::endl;
#endif
				node->m_prev = m_prev;
				node->m_next = this;
				m_prev = node;
			}

			Node(Node* end) : m_data(), m_next(end), m_prev(end) {}
			Node(T data, Node* end) : m_data(data), m_next(end), m_prev(end) {}

			friend class List;
			friend class Allocator<Node>;			
		};

	public:

		struct Iterator
		{
			Node* node;

			Iterator(Node& n) : node(&n) {}

			T& operator -> ()
			{
				return node.m_data;
			}

			T& operator * ()
			{
				return node->m_data;
			}

			Iterator& operator ++ ()
			{
				node = node->m_next;
				return *this;
			}

			Iterator& operator -- ()
			{
				node = node->m_prev;
				return *this;
			}

			bool operator == (const Iterator& it)
			{
				return !memcmp(this, &it, sizeof(Iterator));
			}

			bool operator != (const Iterator& it)
			{
				return !(*this == it);
			}
		};

	public:

		List() : m_head(&m_end), m_tail(&m_end), m_end(0) {}

		~List()
		{
			Node* cur = m_head;
			while (cur != &m_end)
			{
				Node* ptr = cur;
				cur = cur->m_next;				
				Allocator<Node>::Free((void*)ptr);
			}
		}

		void PushBack(T item)
		{
			void* p = Allocator<Node>::Alloc(sizeof(Node));
			Node* new_node = new(p) Node(item, &m_end);

			if (m_head == &m_end && m_tail == &m_end)
				m_head = m_tail = new_node;
			else
			{
				new_node->InsertBefore(m_tail, &m_end);
				m_tail = new_node;
			}
		}

		void PushFront(T item)
		{
			void* p = Allocator<Node>::Alloc(sizeof(Node));
			Node* new_node = new(p) Node(item, &m_end); 

			if (m_head == &m_end && m_tail == &m_end)
				m_head = m_tail = new_node;
			else
			{
				m_head->InsertBefore(new_node, &m_end);
				m_head = new_node;
			}
		}

		void Insert(Iterator& pos, T data)
		{
			Node* new_node = Allocator::Alloc<T>();
			new_node->m_data = data;
			new_node->m_next = &m_end;
			new_node->m_prev = &m_end;

			node->InsertAfter(new_node);
		}

		//	After join list will be empty
		void Join(Iterator& pos, List<T, Allocator>& list)
		{
			Node* local_start = pos.node;
			Node* local_end = pos.node->m_next;

			local_start->m_next = list.m_head;
			local_end->m_prev = list.m_tail;
			list.m_head->m_prev = local_start;
			list.m_tail->m_next = local_end;
			
			list.m_head = &list.m_end;
			list.m_end = &list.m_end;
		}

		void Clone(List<T>& result)
		{			
			for (auto it = Begin(); it != End(); ++it)
			{
				result.PushBack(*it);
			}
		}

		void Erase(Iterator& pos)
		{
			Node* cur = m_head;

			while (cur != pos || cor != &m_end)
				cur = cur->next;
			Node* prev = cur->m_prev;
			Node* next = cur->m_next;
			prev->m_next = next;
			next->m_prev = prev;

			Allocator::Free(cur);
		}
		
		Iterator Begin()
		{
			return Iterator(*m_head);
		}

		Iterator End()
		{
			return Iterator(m_end);
		}

	private:
		Node* m_head;
		Node* m_tail;
		Node m_end;
	};
}

#endif