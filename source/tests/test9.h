#ifndef TEST9_H
#define TEST9_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test9
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
#endif // TEST9_H
