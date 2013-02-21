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
	TerrainManager::TerrainManager(const TerrainManagerDesc& desc)
		: m_desc(desc)
		, m_terrain(nullptr)
	{}

	TerrainManager::~TerrainManager()
	{
		safe_delete(m_terrain);
		//for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		//	safe_delete(*it);
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
			m_terrain = Cast<Terrain*>(Utility::ParsePunkFile(map_file));
			if (!m_terrain)
				throw System::PunkInvalidArgumentException(L"Unable to manage " + map_name);
		}
		else if (!memcmp(buf, "MAPDESCBIN", strlen("MAPDESCBIN")))
		{
			stream.seekg(std::ios_base::beg, 0);
			m_terrain = new Terrain;
			try
			{
				m_terrain->Load(stream);
			}
			catch(...)
			{
				safe_delete(m_terrain);
				throw;
			}
		}
		return true;
	}

	TerrainObserver* TerrainManager::CreateTerrainObserver(const Math::vec3& start_position)
	{
		TerrainViewDesc desc;
		desc.block_scale = m_terrain->GetBlockScale();
		desc.block_size = m_terrain->GetBlockSize();
		desc.manager = this;
		desc.position = start_position.XZ();
		desc.terrain = m_terrain;
		desc.threshold = m_desc.threshold;
		desc.view_size = int(m_desc.view_size);
		TerrainView* view(new TerrainView(desc));
		TerrainObserver* observer(new TerrainObserver(view));
		observer->SetPosition(start_position);
//		m_observers.push_back(observer);
		return observer;//m_observers.back();
	}
}