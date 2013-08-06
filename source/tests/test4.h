#ifndef ROTATE_TRIANGLE_H
#define ROTATE_TRIANGLE_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test4
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

#endif // ROTATE_TRIANGLE_H
