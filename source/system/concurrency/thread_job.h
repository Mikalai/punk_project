#ifndef _H_THREAD_JOB
#define _H_THREAD_JOB

#include "../../config.h"

namespace System
{
	class ThreadPool;

	class PUNK_ENGINE_API ThreadJob
	{
	public:	
		ThreadJob();	
		void Run();
		bool IsComplete();
	private:
		bool m_complete;
		ThreadPool* m_pool;
		friend class ThreadPool;
	protected:
		virtual void RunThread() = 0;
	};
}

#endif