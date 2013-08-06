#ifndef TEST5_H
#define TEST5_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test5
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
