#ifndef _H_PUNK_SYSTEM_STATE
#define _H_PUNK_SYSTEM_STATE

#include <vector>
#include <stack>
#include "smart_pointers/proxy.h"
#include "errors/module.h"
#include "poolable.h"

namespace System
{
	template<class T>
	class State : public Poolable<State<T>>
	{
	public:

		T& Get() { return m_core; }
		const T& Get() const { return m_core; }
	private:
		T m_core;
	};

	template<class T>
	class StateManager
	{
	public:
		StateManager()
		{
			m_current_state = new State<T>;
		}

		~StateManager()
		{
			delete m_current_state;
			m_current_state = 0;
			while (!m_states.empty())
			{
				delete m_states.top();
				m_states.pop();
			}
		}

		State<T>* CurrentState() { return m_current_state; }

		void Push()
		{
			m_states.push(m_current_state);
			m_current_state = new State<T>(*m_current_state);
		}

		bool Pop()
		{
			if (m_states.empty())
				throw System::PunkInvalidArgumentException(L"Error in render state stack");

			delete m_current_state;
			m_current_state = m_states.top();
			m_states.pop();
			return true;
		}

	private:
		State<T>* m_current_state;
		std::stack<State<T>*> m_states;
	};
}

#endif	//	_H_PUNK_SYSTEM_STATE
