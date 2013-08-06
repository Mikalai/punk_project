#ifndef TEST12_H
#define TEST12_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test12
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

#endif // TEST12_H
