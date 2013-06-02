#ifndef _H_PUNK_VIRTUAL_TERRAIN_MANAGER
#define _H_PUNK_VIRTUAL_TERRAIN_MANAGER

#include <memory>
#include "../../config.h"
#include "terrain.h"

namespace Physics { class Simulator; }

namespace Virtual
{
	class TerrainData;
	class TerrainObserver;
	class TerrainView;

	struct TerrainManagerDesc
	{
		unsigned memory_usage;
		float view_size;
		float threshold;
		Physics::Simulator* simulator;

		TerrainManagerDesc()
			: memory_usage(0)
			, view_size(0)
			, threshold(0)
			, simulator(nullptr)
		{}
	};

	class PUNK_ENGINE_API TerrainManager
	{
	public:
		/**
		*	When created it is possible to define maximal allowed memory consumption
		*/
		TerrainManager(const TerrainManagerDesc& desc);
		~TerrainManager();

		/**
		*	Means that current manager should manager map with specified name
		*	From map name it is possible to deduce folder name with scheme and
		*	data, because they are the same
		*/
		bool Manage(const System::string& map_name);

		//System::Proxy<TerrainData> RetreiveTerrainData();
		//System::Proxy<TerrainData> RetreiveTerrainData();

		Terrain* GetTerrain() { return m_terrain; }
		TerrainObserver* CreateTerrainObserver(const Math::vec3& start_position);

		const System::string GetCurrentMap() { return m_current_map; }

		Physics::Simulator* GetPhysicsSimulator() { return m_desc.simulator; }

	private:
		bool Init(const Terrain& terrain);
		bool Clear();

	private:
		TerrainRef m_terrain;
		//std::vector<TerrainObserver*> m_observers;
		TerrainManagerDesc m_desc;
		System::string m_current_map;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_MANAGER
