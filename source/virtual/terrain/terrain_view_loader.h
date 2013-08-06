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
	class TerrainManager;

	struct TerrainViewLoaderDesc
	{
		void* m_buffer;
		unsigned m_buffer_size;
		unsigned m_view_size;
		unsigned m_block_size;
		float m_block_scale;
		Math::vec2 m_view_point;
		Math::vec2 m_world_origin;
		System::string m_map_name;
		TerrainManager* m_manager;
	};

	class PUNK_ENGINE_API TerrainViewLoader : public System::AbstractDataLoader
	{
	public:
		/**
		*	Init constructor with buffer where actual data will be stored
		*/
		TerrainViewLoader(const TerrainViewLoaderDesc& desc);

		/**
		*	Do not destroy anything, because all storage buffers are external
		*/
		virtual ~TerrainViewLoader();
		/**
		*	This will collect data from different cells in the internal buffer
		*/
		virtual System::StreamingStepResult Load();
		/**
		*	This will do nothing 
		*/
		virtual System::StreamingStepResult Decompress(void** data, unsigned* size);
		/**
		*	This will do nothing
		*/
		virtual System::StreamingStepResult Destroy();
	private:
		TerrainViewLoaderDesc m_desc;		
	};
}

#endif // _H_PUNK_VIRTUAL_TERRAIN_VIEW_LOADER
