#ifndef TEST2_H
#define TEST2_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test2
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
