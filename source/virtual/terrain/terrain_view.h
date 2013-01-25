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
#include "../../system/types.h"
#include "../../math/vec2.h"

namespace OpenGL { class Texture2D; }

namespace Virtual
{
	class Terrain;

	class PUNK_ENGINE TerrainView
	{
	public:
		/**
		*	Information about position should be recieved from observer
		*/
		TerrainView(int view_size, int block_size, float block_scale, const Math::vec2 position, System::Proxy<Terrain> terrain);
		~TerrainView();
		
		int GetViewSize() const { return m_view_size; }

		void UpdatePosition(const Math::vec2& value);
		void SetUpdateThreshold(float value);
		
		System::Proxy<OpenGL::Texture2D> GetHeightMap() { return m_height_map_front; }
		void* GetViewData() { return m_front_buffer; }

		System::Proxy<Terrain> GetTerrain() { return m_terrain; }

		const Math::vec2& GetPosition() const { return m_position; }

	private:
		void InitiateAsynchronousUploading();
		static void OnEnd(void* data);

		// size of the cell
		int m_block_size;
		//	scale
		float m_block_scale;
		//	size of the view in meters of game world
		int m_view_size;
		//	front buffer that is used for physics and rendering
		void* m_front_buffer;
		//	back buffer thst is used for asynchronous uploading dat from cells
		void* m_back_buffer;
		//	last world positon of the view center
		Math::vec2 m_position_back;
		//	last world positon of the view center
		Math::vec2 m_position;
		//	Holds unprocessed last position;
		Math::vec2 m_last_unprocessed;
		//	threshold for initating data streaming into the view
		float m_threshold;
		//	Height map for rendering is stored here
		System::Proxy<OpenGL::Texture2D> m_height_map_front;
		//	Height map for asyncloading is stored here
		System::Proxy<OpenGL::Texture2D> m_height_map_back;
		//	flag that indicates that uploading is in process
		bool m_loading;
		//	holds last update result
		unsigned m_result;
		System::Proxy<Terrain> m_terrain;
		//	
		bool m_init;
	};
}

#endif