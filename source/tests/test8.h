#ifndef TEST8_H
#define TEST8_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test8
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
#endif // TEST8_H
