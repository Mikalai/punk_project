#ifndef _H_PUNK_VIRTUAL_TERRAIN_VIEW
#define _H_PUNK_VIRTUAL_TERRAIN_VIEW

/**
*	Terrain view is used for data representation to the othe simulation world.
*	View data is updated when observer changes its world position.
*	View has two data buffers: front and back. While front buffer is used by the simulation
*	back buffer is being asynchronysly processed with uploading data from memory that was
*	allocated for TerrainCells data to the memory of the back buffer.
*	When loading is completed a new height map should be created in order
*	to perform terrain visualizing.
*
*	The main part of the TerrainView is two arrays of data.
*	Also it is known the size of the view in world coordinates.
*/

#include "../../config.h"
#include "../../system/smart_pointers/proxy.h"
#include "../../math/vec2.h"

namespace Gpu { class Texture2D; }
namespace Physics { class Terrain; }
namespace Math { class Line3D; }

namespace Virtual
{
	class Terrain;
	class TerrainManager;

	struct TerrainViewDesc
	{
		//	size of the view in meters of game world
		int view_size;
		// size of the cell
		int block_size;
		//	scale
		float block_scale;
		//	last world positon of the view center
		Math::vec2 position;
		//	terrain scheme can be taken from here
		Terrain* terrain;
		//	accessor to the curre manager
		TerrainManager* manager;
		//	threshold for initating data streaming into the view
		float threshold;
	};

    class PUNK_ENGINE_API TerrainView
	{
	public:
		/**
		*	Information about position should be recieved from observer
		*/
		TerrainView(const TerrainViewDesc& desc);
		~TerrainView();

		int GetViewSize() const { return m_desc.view_size; }

		void UpdatePosition(const Math::vec2& value);
		void SetUpdateThreshold(float value);

		Gpu::Texture2D* GetHeightMap() { return m_height_map_front; }
		void* GetViewData() { return m_front_buffer; }
		const void* GetViewData() const { return m_front_buffer; }
		void* GetBackViewData() { return m_back_buffer; }
		const void* GetBackViewData() const { return m_back_buffer; }
		const Math::vec2& GetBackPosition() const { return m_position_back; }

		Terrain* GetTerrain() { return m_desc.terrain; }

		const Math::vec2& GetPosition() const { return m_desc.position; }

		/**
		*	Calculates height above the surface of the point with
		*	coordinates in world coorinate system
		*/
		float GetHeightAboveSurface(const Math::vec3& world_point);

		/**
		*	Calculates point of intersection line with terrain.
		*	Binary search is used.
		*	Line supposed to be in the world coordinates
		*/
		bool IntersectRay(const Math::Line3D& ray, Math::vec3& result);

		/**
		*	this will copy date to the physics terrain
		*/
		void UpdatePhysics();
	private:
		void InitiateAsynchronousUploading();
		static void OnEnd(void* data);

		//	some data is stored here
		TerrainViewDesc m_desc;
		//	front buffer that is used for physics and rendering
		void* m_front_buffer;
		//	back buffer thst is used for asynchronous uploading dat from cells
		void* m_back_buffer;
		//	last world positon of the view center
		Math::vec2 m_position_back;
		//	Holds unprocessed last position;
		Math::vec2 m_last_unprocessed;
		//	Height map for rendering is stored here
		Gpu::Texture2D* m_height_map_front;
		//	Height map for asyncloading is stored here
		Gpu::Texture2D* m_height_map_back;
		//	flag that indicates that uploading is in process
		bool m_loading;
		//	holds last update result
		unsigned m_result;
		//
		bool m_init;
		//	should be deleted in destructor
		Physics::Terrain* m_bullet_terrain;
	};

	typedef TerrainView* TerrainViewRef;

}

#endif
