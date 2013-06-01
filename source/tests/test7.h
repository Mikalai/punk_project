#ifndef TEST7_H
#define TEST7_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test7
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
