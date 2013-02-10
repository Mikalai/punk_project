#include <fstream>
#include "../../utility/parser/base_parser2.h"
#include "../../system/environment.h"
#include "terrain_view.h"
#include "terrain_observer.h"
#include "terrain_manager.h"
#include "terrain_cell.h"
#include "../../gpu/opengl/textures/texture2d.h"

namespace Virtual
{
	std::unique_ptr<TerrainManager> TerrainManager::m_instance;

	TerrainManager* TerrainManager::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new TerrainManager);
		return m_instance.get();
	}

	void TerrainManager::Destroy()
	{
		m_instance.reset(0);
	}

	TerrainManager::TerrainManager(unsigned max_memory)
		: m_max_memory(max_memory)
	{}

	TerrainManager::~TerrainManager()
	{

	}

	bool TerrainManager::Manage(const System::string& map_name)
	{
		m_current_map = map_name;
		System::string map_file = System::Environment::Instance()->GetMapFolder() + map_name + L"\\map.description";
		std::ifstream stream(map_file.Data(), std::ios_base::binary);
		char buf[16];
		stream.read(buf, 16);
		if (!memcmp(buf, "MAPDESCTEXT", strlen("MAPDESCTEXT")))
		{
			stream.close();
			m_terrain = Utility::ParsePunkFile(map_file);
			if (!m_terrain.IsValid())
				return (out_error() << "Unable to manage " << map_name << std::endl, false);
		}
		else if (!memcmp(buf, "MAPDESCBIN", strlen("MAPDESCBIN")))
		{
			stream.seekg(std::ios_base::beg, 0);
			m_terrain.Reset(new Terrain);
			if (!m_terrain->Load(stream))
				return (out_error() << "Unable to manage " << map_name << std::endl, false);
		}
		return true;
	}

	System::WeakRef<TerrainObserver> TerrainManager::CreateTerrainObserver(const Math::vec3& start_position)
	{
		System::Proxy<TerrainView> view(new TerrainView(1024, m_terrain->GetBlockSize(), m_terrain->GetBlockScale(), start_position.XZ(), m_terrain));
		System::Proxy<TerrainObserver> observer(new TerrainObserver(view));
		observer->SetPosition(start_position);
		m_views.push_back(view);
		m_observers.push_back(observer);
		return m_observers.back();
	}
}