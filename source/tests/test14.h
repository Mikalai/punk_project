#ifndef TEST14_H
#define TEST14_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test14
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
