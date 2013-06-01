#ifndef _H_PUNK_VIRTUAL_TERRAIN
#define _H_PUNK_VIRTUAL_TERRAIN

#include "../../config.h"
#include "../../system/object.h"
#include "../../math/vec2.h"
#include "../../math/smart_matrix.h"
#include "../data/material.h"
#include "terrain_cell.h"

namespace Virtual
{
	class PUNK_ENGINE_PUBLIC Terrain : public System::Object
	{
	public:
		Terrain();
		virtual ~Terrain();

		void SetNumBlocks(int value);
		int GetNumBlocks() const { return m_core.m_num_blocks; }

		void SetBlockScale(float value) { m_core.m_block_scale = value; }
		float GetBlockScale() const { return m_core.m_block_scale; }

		void SetBlocksSize(int value) { m_core.m_block_size = value; }
		int GetBlockSize() const { return m_core.m_block_size; }
		
		void SetHeightScale(float value) { m_core.m_height_scale = value; }
		float GetHeightScale() const { return m_core.m_height_scale; }

		void SetOrigin(const Math::vec2& value) { m_core.m_origin = value; }
		const Math::vec2& GetOrigin() const { return m_core.m_origin; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		const System::string ToString() const;

		bool AddOrUpdateCell(const TerrainCell& value);

		TerrainCell* GetCell(int x, int y) { return m_cells.At(y, x); }
		const TerrainCell* GetCell(int x, int y) const { return m_cells.At(y, x); }

		Material* GetMaterial() { return m_material; }
		void SetMaterial(Material* value) { m_material = value; }

	private:

		struct Core
		{
			char m_head[16];
			int m_num_blocks;
			float m_block_scale;
			int m_block_size;
			float m_height_scale;
			Math::vec2 m_origin;		

			Core();
		};

		Core m_core;

		//	should be destroyed
		Math::Matrix<TerrainCell*> m_cells;
		Material* m_material;
	};

	typedef Terrain* TerrainRef;
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN
