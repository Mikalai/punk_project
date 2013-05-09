#ifndef _H_PUNK_OPENGL_SCALED_GRID
#define _H_PUNK_OPENGL_SCALED_GRID

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL

namespace GPU
{
#ifdef USE_OPENGL
	using ScaledGridObjectBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
	Vertex<VertexComponent::Position,
	VertexComponent::Normal,
	VertexComponent::Texture0>>;
#else
#endif	//	USE_OPENGL

	class PUNK_ENGINE ScaledGridObject : public ScaledGridObjectBase
	{
		using Base = ScaledGridObjectBase;

	public:

		ScaledGridObject(VideoDriver* driver) : Base(driver) {}

		virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels);

		float GetTotalWidth() const;
		float GetTotalHeight() const;

	private:

		ScaledGridObject(const ScaledGridObject& quad) = delete;
		ScaledGridObject& operator = (const ScaledGridObject& quad) = delete;

		float m_total_width;
		float m_total_height;
	};
}

#endif	//	_H_PUNK_OPENGL_SCALED_GRID
