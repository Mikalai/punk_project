#ifndef TEST3_H
#define TEST3_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test3
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

#endif // TEST5_H
