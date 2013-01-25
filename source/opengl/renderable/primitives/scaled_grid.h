#ifndef _H_PUNK_OPENGL_SCALED_GRID
#define _H_PUNK_OPENGL_SCALED_GRID

#include "vertex_array_object.h"

namespace OpenGL
{
	class PUNK_ENGINE ScaledGridObject : public VertexArrayObject2<GL_TRIANGLES, Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TEXTURE>
	{
		enum { PrimitiveType = GL_TRIANGLES };
		enum { VertexType = Utility::COMPONENT_POSITION|
			Utility::COMPONENT_NORMAL|
			Utility::COMPONENT_TEXTURE};

	public:

		ScaledGridObject::ScaledGridObject() {}

		virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels);

	private:
		ScaledGridObject(const ScaledGridObject& quad);
		ScaledGridObject& operator = (const ScaledGridObject& quad);
	};
}

#endif	//	_H_PUNK_OPENGL_SCALED_GRID