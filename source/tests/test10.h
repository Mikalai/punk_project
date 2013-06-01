#ifndef TEST10_H
#define TEST10_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test10
{
	class Test : public TestInterface
	{
	public:
		void Run();
		bool Succeed();

	private:
		bool m_result;
	};
}

#endif // TEST10_H
