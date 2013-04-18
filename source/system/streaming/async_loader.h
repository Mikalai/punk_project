#ifndef _H_PUNK_SYSTEM_ASYNC_LOADER
#define _H_PUNK_SYSTEM_ASYNC_LOADER

#include <memory>
#include <deque>
#include <vector>
#include "../../config.h"
#include "../concurrency/thread_mutex.h"
#include "../concurrency/semaphore.h"
#include "../concurrency/thread.h"
#include "resource_request.h"

namespace System
{
	class PUNK_ENGINE AsyncLoader
	{
	public:
		bool InitAsyncLoading(int num_process_threads);
		void DestroyAsyncLoading();

		int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result);
		unsigned FileIOThreadProc();
		unsigned ProcessingThreadProc();
		unsigned MainThreadProc(unsigned num_to_process);

		static AsyncLoader* Instance();
		static void Destroy();
	private:
		static std::unique_ptr<AsyncLoader> m_instance;

		std::deque<ResourceRequest> m_io_queue;
		std::deque<ResourceRequest> m_process_queue;
		std::deque<ResourceRequest> m_render_queue;
		bool m_io_done_flag;
		bool m_process_done_flag;
		bool m_global_done_flag;
		ThreadMutex m_io_queue_mutex;
		ThreadMutex m_process_queue_mutex;
		ThreadMutex m_render_queue_mutex;
		Semaphore m_io_thread_semaphore;
		Semaphore m_process_thread_semaphore;
		Thread m_io_thread;
		std::vector<Thread> m_process_threads;
		unsigned m_num_io_requests;
		unsigned m_num_process_requests;
	};
}

#endif	//	_H_PUNK_SYSTEM_ASYNC_LOADER
