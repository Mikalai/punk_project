#ifndef _H_PUNK_VIRTUAL_TERRAIN_MANAGER
#define _H_PUNK_VIRTUAL_TERRAIN_MANAGER

#include "../../config.h"
#include "terrain.h"

namespace Virtual
{
	class TerrainData;
	class TerrainObserver;
	class TerrainView;

	class PUNK_ENGINE TerrainManager 
	{
	public:
		/**
		*	When created it is possible to define maximal allowed memory consumption
		*/
		TerrainManager(unsigned max_memory = std::numeric_limits<unsigned>::max());
		~TerrainManager();
		
		/**
		*	Means that current manager should manager map with specified name
		*	From map name it is possible to deduce folder name with scheme and
		*	data, because they are the same
		*/
		bool Manage(const System::string& map_name);

		//System::Proxy<TerrainData> RetreiveTerrainData();
		//System::Proxy<TerrainData> RetreiveTerrainData();

		static TerrainManager* Instance();
		static void Destroy();
	private:
		bool Init(const Terrain& terrain);
		bool Clear();
		//std::vector<System::Proxy<TerrainData>> m_terrain_data;
		std::vector<System::Proxy<TerrainObserver>> m_observers;
		std::vector<System::Proxy<TerrainView>> m_views;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_MANAGER