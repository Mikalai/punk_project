#ifndef TEST15_H
#define TEST15_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test15
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
