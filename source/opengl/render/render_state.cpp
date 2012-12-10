#include "render_state.h"

namespace OpenGL
{
	void StateManager::Push()
	{
		m_states.push(m_current_state);
		m_current_state.Reset(new State(*m_current_state));
	}

	bool StateManager::Pop()
	{		
		if (m_states.empty())
			return (out_error() << "Error in render state stack" << std::endl, false);

		m_current_state = m_states.top();
		m_states.pop();
		return true;
	}

	void StateManager::Clear()
	{
	}

	void StateManager::Init()
	{		
		m_current_state.Reset(new State);
	}
}
