#ifndef _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER
#define _H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER

#include "../../../config.h"

namespace System
{
	class PUNK_ENGINE AbstractDataLoader
	{
	public:
		virtual ~AbstractDataLoader() {}
		
		/**
		*	when 0 returns it means an error
		*/
		virtual unsigned Load() = 0;
		
		/**
		*	when 0 returns it means an error
		*/
		virtual unsigned Decompress(void** data, unsigned* size) = 0;

		/**
		*	when 0 returns it means an error
		*/
		virtual unsigned Destroy() = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_STREAM_ABSTRACT_DATA_LOADER