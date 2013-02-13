#ifndef _H_PUNK_SCENE_TERRAIN_NODE
#define _H_PUNK_SCENE_TERRAIN_NODE

#include "../config.h"
#include "node.h"

namespace Virtual { class TerrainObserver; }

namespace Scene
{
	class PUNK_ENGINE TerrainNode : public Node
	{
	public:

		TerrainNode();
		~TerrainNode();

		void SetTerrainObserver(Virtual::TerrainObserver* value) { m_observer = value; }
		Virtual::TerrainObserver* GetTerrainObserver() { return m_observer; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static TerrainNode* CreateFromFile(const System::string& path);
		static TerrainNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);							

	private:		
		Virtual::TerrainObserver* m_observer;		
	};
}

//REGISTER_MANAGER(L"resource.terrains", L"*.terrain", System::Environment::Instance()->GetModelFolder(), System::ObjectType::T, Scene, GeometryNode, return, return);

#endif	//	_H_PUNK_SCENE_TERRAIN_NODE
