#include "async_loader.h"
#include "data_loader.h"
#include "data_processor.h"

namespace System
{
	unsigned __stdcall IOThread(void* data)
	{
		if (data == nullptr)
			return 0;
		return reinterpret_cast<AsyncLoader*>(data)->FileIOThreadProc();
	}

	unsigned __stdcall ProcessThread(void* data)
	{
		if (data == nullptr)
			return 0;
		return reinterpret_cast<AsyncLoader*>(data)->ProcessingThreadProc();
	}

	bool AsyncLoader::InitAsyncLoading(int num_process_threads)
	{
		m_io_thread_semaphore.Create(LONG_MAX);
		m_process_thread_semaphore.Create(LONG_MAX);
		
		m_process_threads.resize(num_process_threads);
		for (auto it = m_process_threads.begin(); it != m_process_threads.end(); ++it)
		{
			it->Create(ProcessThread, (void*)this);
			it->Resume();
		}

		m_io_thread.Create(IOThread, (void*)this);
		return true;
	}

	/**
	*	This method initiates process of loading data from hard drive 
	*	that finaly should lead to the uploading data to the device 
	*	memory
	*/
	int AsyncLoader::AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result)
	{
		int res = -1;
		//	check input data
		if (!loader || !processor)
			return res;

		//	create initial request
		ResourceRequest request;
		request.m_loader = loader;		
		request.m_processor = processor;
		request.m_result = result;
		request.m_lock_flag = false;
		request.m_valid_flag = true;
		request.m_task = ResourceRequest::LOAD;

		//	add request to input queue
		m_io_queue_mutex.Lock();		
		m_io_queue.push_back(request);
		res = (int)m_io_queue.size() - 1;
		m_io_queue_mutex.Unlock();

		//	allow io thread to do job
		m_io_thread_semaphore.Release();

		return res;
	}

	/*
	*	This method works in separate thread and can load
	*	data from hard driver using data loader 
	*	and can upload data from host memory to device memory
	*	using data processor
	*/
	unsigned AsyncLoader::FileIOThreadProc()
	{
		ResourceRequest request;
		m_io_done_flag = false;
		while(!m_global_done_flag)
		{
			//	wait till the task will be added
			m_io_thread_semaphore.Wait();

			//	check if program terminated
			if (m_global_done_flag)
				break;

			//	fetch request using critical section
			m_io_queue_mutex.Lock();
			request = m_io_queue.front();
			m_io_queue.pop_front();
			m_io_queue_mutex.Unlock();

			//	check requested operation			
			//	LOAD - from hard drive data loading
			if (ResourceRequest::LOAD == request.m_task)	
			{
				//	check if the request is valid
				if (request.m_valid_flag)
				{
					if (!request.m_loader->Load())
					{
						request.m_valid_flag = false;
					}					
				}

				//	if request is not valid we simply bypass it to the next stag, because only
				//	somewhere their it will be destroyed
				m_process_queue_mutex.Lock();
				m_process_queue.push_back(request);
				m_process_queue_mutex.Unlock();

				//	allow process threads to next tasks to the request
				m_process_thread_semaphore.Release();
			}

			//	we need to copy data from host memory to the device memory
			else if (ResourceRequest::COPY_TO_DEVICE == request.m_task)
			{
				//	check is request is still valid
				if (request.m_valid_flag)
				{
					//	try to copy data to device memory
					if (!request.m_processor->CopyToResource())
					{
						//	if troubles invalidate request
						request.m_valid_flag = false;
					}
				}

				//	unlock this resource, seems that it means that data
				//	is in device memory or error was now, and we don't need request to exist any
				//	more
				request.m_lock_flag = false;

				//	add request to the main thread queue
				m_render_queue_mutex.Lock();
				m_render_queue.push_back(request);
				m_render_queue_mutex.Unlock();
			}
		}

		m_io_done_flag = true;
		return m_io_done_flag;
	}

	unsigned AsyncLoader::ProcessingThreadProc()
	{
		ResourceRequest request;
		//	set process thread done flag as false
		m_process_done_flag = false;

		//	if program is not end
		while (!m_global_done_flag)
		{
			//	wait till the tasks in processing queue
			m_process_thread_semaphore.Wait();
			if (m_global_done_flag)
				break;

			//	fetch request from the processing queue
			m_process_queue_mutex.Lock();
			request = m_process_queue.front();
			m_process_queue.pop_front();
			m_process_queue_mutex.Unlock();

			//	check if request is still valid
			if (request.m_valid_flag)
			{
				void* data;
				unsigned size;
				//	decompress data using loader
				if (request.m_loader->Decompress(&data, &size))
				{
					// process data using processor
					if (!request.m_processor->Process(data, size))
					{
						//	if failed set request is invalid
						request.m_valid_flag = false;
					}
				}
				else
					//	if decompress failed set request as invalid
					request.m_valid_flag = false;
			}
			
			//	lock request, that means we are gonna copy data from 
			//	host to device in the render thread
			request.m_lock_flag = true;

			//	add request to the render thread queue
			m_render_queue_mutex.Lock();
			m_render_queue.push_back(request);
			m_render_queue_mutex.Unlock();
		}

		//	mark thread as finished
		m_process_done_flag = true;
		return m_process_done_flag;
	}

	/**
	*	This method will terminate io and processing threads
	*/
	void AsyncLoader::DestroyAsyncLoading()
	{
		//	declare end of work
		m_global_done_flag = true;

		//	release semaphores to allow them
		//	checking global done flag (which is true now)
		//	 that will allow thread to commit suicide
		//	successfuly without any TerminateThread procedures
		m_io_thread_semaphore.Release();
		m_process_thread_semaphore.Release();

		//	Wait till thread are done
		while (!m_io_done_flag || !m_process_done_flag)
		{
			//	Confusing a bit, but still should work
			Sleep(100);
		}

		//	destroy all semaphores
		m_io_thread_semaphore.Destroy();
		m_process_thread_semaphore.Destroy();

		//	destroy all mutexes
		m_io_queue_mutex.Destroy();
		m_process_queue_mutex.Destroy();

		//	destroy all process handles
		for (auto it = m_process_threads.begin(); it != m_process_threads.end(); ++it)
			it->Destroy();

		//	destroy io thread
		m_io_thread.Destroy();
	}
}