#ifndef _H_PUNK_SYSTEM_STATE
#define _H_PUNK_SYSTEM_STATE

#include <vector>
#include <stack>
#include "smart_pointers/proxy.h"

namespace System
{
	template<class T>
	class State
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
		StateManager() { m_current_state.Reset(new State<T>); }
		System::Proxy<State<T>> CurrentState() { return m_current_state; }

		void Push()
		{
			m_states.push(m_current_state);
			m_current_state.Reset(new State<T>(*m_current_state));
		}

		bool Pop()
		{
			if (m_states.empty())
				return (out_error() << "Error in render state stack" << std::endl, false);

			m_current_state = m_states.top();
			m_states.pop();
			return true;
		}

	private:
		System::Proxy<State<T>> m_current_state;
		std::stack<System::Proxy<State<T>>> m_states;
	};	
}

#endif	//	_H_PUNK_SYSTEM_STATE