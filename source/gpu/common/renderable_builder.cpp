#include "renderable_builder.h"
#include "../opengl/renderable/gl_renderable_builder.h"

namespace GPU
{
	RenderableBuilder::RenderableBuilder(VideoDriver* driver)
		: impl(new RenderableBuilderImpl(driver))
	{}

	RenderableBuilder::~RenderableBuilder()
	{
		delete impl;
		impl = nullptr;
	}

	void RenderableBuilder::Begin(const PrimitiveType& type)
	{
		impl->Begin(type);
	}

	void RenderableBuilder::End()
	{
		impl->End();
	}

	void RenderableBuilder::Vertex3f(float x, float y, float z)
	{
		impl->Vertex3f(x, y, z);
	}

	void RenderableBuilder::Vertex3fv(float* value)
	{
		impl->Vertex3fv(value);
	}
}
