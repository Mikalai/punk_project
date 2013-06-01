#include "terrain_observer.h"
#include "terrain_view.h"

namespace Virtual
{
	TerrainObserver::TerrainObserver(TerrainView* view)
		: m_view(view)
	{
	}

	void TerrainObserver::SetPosition(const Math::vec3& value)
	{
		m_view->UpdatePosition(value.XZ());
	}

	TerrainObserver::~TerrainObserver()
	{
		safe_delete(m_view);
	}
}