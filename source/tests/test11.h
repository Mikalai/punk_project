#ifndef TEST11_H
#define TEST11_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test11
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
