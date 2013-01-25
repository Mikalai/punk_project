#ifndef _H_PUNK_VIRTUAL_TERRAIN_OBSERVER
#define _H_PUNK_VIRTUAL_TERRAIN_OBSERVER

#include "../../config.h"
#include "../../system/object.h"
#include "../../math/vec3.h"

namespace Virtual
{
	class TerrainManager;
	class TerrainView;

	class PUNK_ENGINE TerrainObserver : public System::Object
	{
	public:
		~TerrainObserver();

		System::Proxy<TerrainView> GetTerrainView() { return m_view; }
		const System::Proxy<TerrainView> GetTerrainView() const { return m_view; }

		void SetPosition(const Math::vec3& value);

	private:
		TerrainObserver(System::Proxy<TerrainView> view);

	private:
		System::Proxy<TerrainView> m_view;
		friend class TerrainManager;
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_OBSERVER
