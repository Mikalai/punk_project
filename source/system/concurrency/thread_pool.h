#ifndef _H_THREAD_POOL
#define _H_THREAD_POOL

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#endif

#include <vector>
#include <stack>
#include <queue>

#include "../../config.h"
#include "thread_job.h"
#include "thread.h"
#include "monitor.h"
#include "atomicint.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC ThreadPool
	{		
		std::queue<ThreadJob*> m_jobs;
		ThreadPool(const ThreadPool& pool);
		ThreadPool& operator = (const ThreadPool&);

        std::vector<Thread> m_threads;
        Thread m_own_thread;
        Monitor m_monitor;

        AtomicInt m_finish;

	public:
		ThreadPool(int threads_count = 4);
		~ThreadPool();

		void ExecuteJob(ThreadJob* job);

		void Lock();
		void Unlock();

		void Join();

		bool IsFinish();
		int HasJobs();

	private:
		void Init(int thread_count);

		ThreadJob* GetThreadJob();

        static unsigned PUNK_STDCALL ThreadFunc(void* data);
        static unsigned PUNK_STDCALL OwnFun(void* data);
	};
}

#endif
