#ifndef _H_PUNK_SYSTEM_STREAMING_RESOURCE_REQUEST
#define _H_PUNK_SYSTEM_STREAMING_RESOURCE_REQUEST

namespace System
{
	class AbstractDataLoader;
	class AbstractDataProcessor;

	enum class StreamingStepResult { STREAM_ERROR, STREAM_TRY_AGAIN, STREAM_OK };

	struct ResourceRequest
	{
		enum Task { LOAD, COPY_TO_DEVICE, LOCK, UNLOCK };
		AbstractDataLoader* m_loader;
		AbstractDataProcessor* m_processor;
		unsigned* m_result;
		//bool m_lock_flag;
		bool m_valid_flag;
		Task m_task;
		void (*on_end_callback)(void*);
		void* m_on_end_data;
	};
}

#endif	//	_H_PUNK_SYSTEM_STREAMING_RESOURCE_REQUEST