#include "mega_destroyer.h"

namespace System
{
	std::unique_ptr<MegaDestroyer> MegaDestroyer::m_instance;

	MegaDestroyer* MegaDestroyer::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new MegaDestroyer);
		return m_instance.get();
	}

	void MegaDestroyer::Destroy()
	{
		m_instance.reset(nullptr);
	}

	void MegaDestroyer::PushDestroyer(MegaDestroyer::Destroyer value)
	{
		m_destroyers.push(value);
	}

	MegaDestroyer::~MegaDestroyer()
	{
		while (!m_destroyers.empty())
		{
			Destroyer top = m_destroyers.top();
			top();
			m_destroyers.pop();
		}
	}
}