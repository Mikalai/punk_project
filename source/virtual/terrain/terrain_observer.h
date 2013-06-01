#ifndef _H_PUNK_VIRTUAL_TERRAIN_OBSERVER
#define _H_PUNK_VIRTUAL_TERRAIN_OBSERVER

#include "../../config.h"
#include "../../system/object.h"
#include "../../math/vec3.h"

namespace Virtual
{
	class TerrainManager;
	class TerrainView;

	class PUNK_ENGINE_PUBLIC TerrainObserver : public System::Object
	{
	public:
		virtual ~TerrainObserver();

		TerrainView* GetTerrainView() { return m_view; }
		const TerrainView* GetTerrainView() const { return m_view; }

		void SetPosition(const Math::vec3& value);

	private:
		TerrainObserver(TerrainView* view);

	private:
		//	should be destroyed in destructor
		TerrainView* m_view;
		friend class TerrainManager;
	};

	typedef TerrainObserver* TerrainObserverRef;
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_OBSERVER
