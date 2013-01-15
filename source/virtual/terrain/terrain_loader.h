#ifndef _H_PUNK_VIRTUAL_TERRAIN_LOADER
#define _H_PUNK_VIRTUAL_TERRAIN_LOADER

#include "../../system/streaming/module.h"
#include "../../math/vec2.h"
#include "../../system/smart_pointers/proxy.h"

namespace Virtual
{
	class TerrainCell;

	class PUNK_ENGINE TerrainLoader : public System::AbstractDataLoader
	{		
	public:
		TerrainLoader(const System::string& map_name, const Math::ivec2& block);
		
		/**
		*	When load is called based on map name and current block
		*	filename is deduced. File opens and data is read in internal buffer
		*/
		virtual unsigned Load();
		
		/**
		*	On decompress internal buffer data is returned.
		*	User should free data himself
		*/
		virtual unsigned Decompress(void** data, unsigned* size);

		/**
		*	Destroy do nothing, because data is returned to the user owning
		*/
		virtual unsigned Destroy();

		virtual ~TerrainLoader();

	private:		
		System::string m_map_name;
		Math::ivec2 m_block;
		
		//	data is loaded here
		int m_size;
		void* m_data;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_LOADER