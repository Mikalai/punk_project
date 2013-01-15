#ifndef _H_PUNK_VIRTUAL_TERRAIN_VIEW_LOADER
#define _H_PUNK_VIRTUAL_TERRAIN_VIEW_LOADER

/**
*	Terrain view loader is implemented because it is requred to copy data from
*	cells that are already loaded or not. 
*/

#include "../../config.h"
#include "../../math/vec2.h"
#include "../../system/streaming/data_loader.h"

namespace Virtual
{
	class PUNK_ENGINE TerrainViewLoader : public System::AbstractDataLoader
	{
	public:
		/**
		*	Init constructor with buffer where actual data will be stored
		*/
		TerrainViewLoader(void* buffer, unsigned buffer_size, unsigned view_size, const Math::vec2& map_position);
		/**
		*	Do not destroy anything, because all storage buffers are external
		*/
		virtual ~TerrainViewLoader();
		/**
		*	This will collect data from different cells in the internal buffer
		*/
		virtual unsigned Load();
		/**
		*	This will do nothing 
		*/
		virtual unsigned Decompress(void** data, unsigned* size);
		/**
		*	This will do nothing
		*/
		virtual unsigned Destroy();
	private:
		void* m_buffer;		
		unsigned m_buffer_size;
		unsigned vm_iew_size;
		Math::vec2 m_map_position;
	};
}

#endif _H_PUNK_VIRTUAL_TERRAIN_VIEW_LOADER