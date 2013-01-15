#ifndef _H_PUNK_VIRTUAL_TERRAIN_PROCESSOR
#define _H_PUNK_VIRTUAL_TERRAIN_PROCESSOR

#include "../../config.h"
#include "../../system/smart_pointers/proxy.h"
#include "../../system/streaming/data_processor.h"

namespace Virtual
{
	class TerrainCell;

	class PUNK_ENGINE TerrainProcessor : public System::AbstractDataProcessor
	{
	public:

		enum Result { RESULT_ERROR = 0, RESULT_TRY_AGAIN = 1, RESULT_OK = 2 };

		TerrainProcessor(System::Proxy<TerrainCell> cell);

		/**
		*	When lock is called for terrain it looks for the suitable image cache
		*	if no data found in cache a new one attempts to create. If no memory
		*	available than any unused image is looked for and freed. If no unused 
		*	images found, or there is no memory available than also try later is returned
		*	If resource if found than it maps to the process memory
		*/
		virtual unsigned LockDeviceObject();

		/**
		*	Unmap all device pointers
		*/
		virtual unsigned UnlockDeviceObject();

		/**
		*	Recieves pointer for data
		*/
		virtual unsigned Process(void* data, unsigned size);

		/**
		*	Actually performs data copy from host to device
		*/
		virtual unsigned CopyToResource();

		/**
		*	Marks resource as error
		*/
		virtual unsigned SetResourceError();

		/**
		*	actually do nothing, because data array of height is
		*	transmitted to TerrainData, that is responsible for
		*	deallocating it 
		*/
		virtual ~TerrainProcessor();

	private:
		//	data and size from loader
		void* m_data;
		unsigned size;
		//	Destination for data. It can be either created or reused
		System::Proxy<TerrainCell> m_terrain_cell;
		//	This is used as cache manager
		
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_PROCESSOR