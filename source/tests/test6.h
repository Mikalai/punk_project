#ifndef TEST6_H
#define TEST6_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test6
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
