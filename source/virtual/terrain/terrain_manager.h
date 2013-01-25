#ifndef _H_PUNK_VIRTUAL_TERRAIN_MANAGER
#define _H_PUNK_VIRTUAL_TERRAIN_MANAGER

#include <memory>
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

		System::Proxy<Terrain> GetTerrain() { return m_terrain; }
		System::Proxy<TerrainObserver> CreateTerrainObserver(const Math::vec3& start_position);

		const System::string GetCurrentMap() { return m_current_map; }

	private:
		static std::unique_ptr<TerrainManager> m_instance;
		bool Init(const Terrain& terrain);
		bool Clear();

	private:
		System::Proxy<Terrain> m_terrain;
		std::vector<System::Proxy<TerrainObserver>> m_observers;
		std::vector<System::Proxy<TerrainView>> m_views;
		unsigned m_max_memory;
		System::string m_current_map;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_MANAGER