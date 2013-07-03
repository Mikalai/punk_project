#ifndef _H_PUNK_SCENE_TERRAIN_NODE
#define _H_PUNK_SCENE_TERRAIN_NODE

#include "../config.h"
#include "node.h"

namespace Virtual
{
    class TerrainObserver;
    class StaticGeometry;
    class TerrainMesh;
}

namespace Scene
{
	class PUNK_ENGINE_API TerrainNode : public Node
	{
	public:

		TerrainNode();
        virtual ~TerrainNode();

		void SetTerrainObserver(Virtual::TerrainObserver* value) { m_observer = value; }
		Virtual::TerrainObserver* GetTerrainObserver() { return m_observer; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static TerrainNode* CreateFromFile(const System::string& path);
		static TerrainNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);							

        void SetTerrainMesh(Virtual::TerrainMesh* value);
        Virtual::TerrainMesh* GetTerrainMesh();

        virtual Node* Clone() const override;
	private:		
        Virtual::TerrainObserver* m_observer;
        Virtual::TerrainMesh* m_mesh;
	};
}

#endif	//	_H_PUNK_SCENE_TERRAIN_NODE
