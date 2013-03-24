#ifdef _WIN32
#include <process.h>
#endif	//	_WIN32
#include "thread_pool.h"

namespace System
{

	ThreadPool::ThreadPool(int thread_count)
	{
		Init(thread_count);
	}

	ThreadPool::~ThreadPool()
	{
#ifdef _WIN32
		for each (HANDLE thread in m_threads)
		{
			CloseHandle(thread);
		}
		DeleteCriticalSection(&m_cs);	
#endif	//	_WIN32
	}

	unsigned __stdcall ThreadPool::ThreadFunc(void* data)
	{
		ThreadPool* pool = reinterpret_cast<ThreadPool*>(data);
		try
		{
			while (1)
			{
				if (!pool->HasJobs() && pool->IsFinish())
					return 0;
				ThreadJob* job = pool->GetThreadJob();
				if (!job)
					return 0;
				job->Run();
				job->m_complete = true;
			}
		}
		catch (...)
		{
			return -1;
		}
		return 0;
	}

	void ThreadPool::Init(int thread_count)
	{
#ifdef _WIN32
		InitializeConditionVariable(&m_cond);
		InitializeCriticalSection(&m_cs);
		m_finish = 0;

		m_threads.resize(thread_count);
		for(auto it = m_threads.begin(); it != m_threads.end(); ++it)
		{
			HANDLE& thread = *it;
			thread = (HANDLE)_beginthreadex(0, 100, ThreadFunc, this, 0, 0);
		}
#endif	//	_WIN32
	}

	ThreadJob* ThreadPool::GetThreadJob()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_cs);
		if (m_jobs.empty())
			SleepConditionVariableCS(&m_cond, &m_cs, INFINITE);

		if (m_jobs.empty())
			return 0;

		ThreadJob* job = m_jobs.front();
		m_jobs.pop();
		LeaveCriticalSection(&m_cs);
#endif	//	_WIN32
		return job;
	}

	void ThreadPool::ExecuteJob(ThreadJob* job)
	{
#ifdef _WIN32
		EnterCriticalSection(&m_cs);
		m_jobs.push(job);
		WakeConditionVariable(&m_cond);
		LeaveCriticalSection(&m_cs);
#endif	//	_WIN32
	}

	void ThreadPool::Lock()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_cs);
#endif	//	_WIN32
	}

	void ThreadPool::Unlock()
	{
#ifdef _WIN32
		LeaveCriticalSection(&m_cs);
#endif	//	_WIN32
	}

	void ThreadPool::Join()
	{
#ifdef _WIN32
		InterlockedIncrement(&m_finish);
		WaitForMultipleObjects(m_threads.size(), &m_threads[0], TRUE, INFINITE);
#endif	//	_WIN32
	}

	bool ThreadPool::IsFinish()
	{
		return m_finish == 1;
	}

	int ThreadPool::HasJobs()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_cs);
		int tasks = m_jobs.size();
		LeaveCriticalSection(&m_cs);
#endif	//	_WIN32
		return tasks;
	}

}