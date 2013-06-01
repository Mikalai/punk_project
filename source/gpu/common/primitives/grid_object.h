#ifndef _H_PUNK_OPENGL_MODULE_GRID_OBJECT
#define _H_PUNK_OPENGL_MODULE_GRID_OBJECT

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{
#ifdef USE_OPENGL
	using GridObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Texture0,
	VertexComponent::Flag>>;
#else
#endif

	class PUNK_ENGINE_PUBLIC GridObject : public GridObjectBase
	{
		using Base = GridObjectBase;
	public:

		GridObject(VideoDriver* driver) : GridObjectBase(driver) {}

		virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices);

	private:
		GridObject(const GridObject& quad) = delete;
		GridObject& operator = (const GridObject& quad) = delete;
	};
}
#endif
