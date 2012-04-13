#ifndef _H_PUNK_OPENGL_MODULE_GRID_OBJECT
#define _H_PUNK_OPENGL_MODULE_GRID_OBJECT

#include "vertex_array_object.h"

namespace OpenGL
{
	struct GridObjectImpl;

	class MODULE_OPENGL GridObject : public VertexArrayObject
	{
	public:
		GridObject();
		GridObject(const GridObject& quad);
		GridObject& operator = (const GridObject& quad);

		void SetWidth(float width);
		void SetHeight(float height);
		void SetWidthSlice(unsigned count);
		void SetHeightSlice(unsigned count);

	protected:
		virtual void Cook();		
	};
}

#endif