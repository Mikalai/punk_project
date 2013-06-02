#ifndef _H_PUNK_VIRTUAL_TERRAIN_DATA
#define _H_PUNK_VIRTUAL_TERRAIN_DATA

#include "../../config.h"
#include "../../string/string.h"

namespace Virtual
{
	class PUNK_ENGINE_API TerrainData
	{
	public:
		TerrainData() : m_data(nullptr) {}
				
		float Value(int x, int y, int block_size)
		{
			return *((float*)m_data + block_size * y + x);
		}

		void SetData(void* data) { m_data = data; }
        ~TerrainData() { delete[] (float*)m_data; }

	private:		
		//	height map data
		void* m_data;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_DATA
