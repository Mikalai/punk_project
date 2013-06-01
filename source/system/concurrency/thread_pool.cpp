#include "atomic.h"
#include "thread_pool.h"

namespace System
{

	ThreadPool::ThreadPool(int thread_count)
	{
		Init(thread_count);
	}

	ThreadPool::~ThreadPool()
	{
	}

#ifdef _WIN32
	unsigned PUNK_STDCALL ThreadPool::ThreadFunc(void* data)
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
#elif defined __gnu_linux__
    void* ThreadPool::ThreadFunc(void* data)
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
            return (void*)-1;
        }
        return nullptr;
    }
#endif

	void ThreadPool::Init(int thread_count)
	{
        Monitor.Init();
        m_finish.Store(0);

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
        m_monitor.Lock();
		if (m_jobs.empty())
            m_monitor.Wait();

		if (m_jobs.empty())
			return 0;

		ThreadJob* job = m_jobs.front();
		m_jobs.pop();
        m_monitor.Unlock();
		return job;
	}

	void ThreadPool::ExecuteJob(ThreadJob* job)
	{
        m_monitor.Lock();
		m_jobs.push(job);
        m_monitor.Pulse();
        m_monitor.Unlock();
	}

	void ThreadPool::Lock()
	{
        m_monitor.Lock();
	}

	void ThreadPool::Unlock()
	{
        m_monitor.Unlock();
	}

	void ThreadPool::Join()
	{
        m_finish.FetchAndAddOrdered(1);
        for (size_t i = 0; i != m_threads.size(); ++i)
            m_threads[i].Join();
	}

	bool ThreadPool::IsFinish()
	{
        return m_finish == 1;
	}

	int ThreadPool::HasJobs()
	{
        m_monitor.Lock();
		int tasks = m_jobs.size();
        m_monitor.Unlock();
		return tasks;
	}

}
