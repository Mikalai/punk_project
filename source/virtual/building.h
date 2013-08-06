#ifndef _H_PUNK_BUILDING
#define _H_PUNK_BUILDING

#include "../../system/types.h"
#include "static_mesh.h"

namespace Utility
{
	class BuildingCore
	{
	public:

	private:

		std::vector<Utility::StaticMesh> m_collision;
	};

	typedef BuildingCore* BuildingCoreRef;

	class Building
	{
		BuildingCoreRef m_core;
	public:

		Building();
		Building(const Building& building);
		Building& operator = (const Building& building);
		~Building();

		void OnInteractWith(const System::string& interaction, const System::string& object, const System::Handler& handler);

	private:

		typedef std::map<System::string, std::map<System::string, System::Handler>> HandlerCollection;
		HandlersCollection m_handlers;

	};
}

#endif	//	_H_PUNK_BUILDING