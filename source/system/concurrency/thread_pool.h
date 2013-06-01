#ifndef _H_THREAD_POOL
#define _H_THREAD_POOL

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif	//	_WIN32

#include <vector>
#include <stack>
#include <queue>

#include "../../config.h"
#include "thread_job.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC ThreadPool
	{		
		std::queue<ThreadJob*> m_jobs;
		ThreadPool(const ThreadPool& pool);
		ThreadPool& operator = (const ThreadPool&);

#ifdef _WIN32
		std::vector<HANDLE> m_threads;
		HANDLE m_own_thread;
		CONDITION_VARIABLE m_cond;
		CRITICAL_SECTION m_cs;
#endif	//	_WIN32
		unsigned long m_finish;

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

		static unsigned __stdcall ThreadFunc(void* data);
		static unsigned __stdcall OwnFun(void* data);
	};
}

#endif
