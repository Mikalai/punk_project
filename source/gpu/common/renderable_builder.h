#ifndef _H_PUNK_GPU_RENDERABLE_BUILDER
#define _H_PUNK_GPU_RENDERABLE_BUILDER

#include "../../config.h"

namespace GPU
{
	enum class PrimitiveType;

	struct RenderableBuilderImpl;
	class VideoDriver;

	class PUNK_ENGINE RenderableBuilder final
	{
	public:
		RenderableBuilder(VideoDriver* driver);
		~RenderableBuilder();

		void Begin(const PrimitiveType& value);
		void Vertex3f(float x, float y, float z);
		void Vertex3fv(float* value);
		void End();
		
		RenderableBuilderImpl* impl;

	private:
		RenderableBuilder(const RenderableBuilder&);
		RenderableBuilder(const RenderableBuilder&&);
		RenderableBuilder& operator = (const RenderableBuilder&);
		RenderableBuilder& operator = (const RenderableBuilder&&);
	};
}

#endif	//	_H_PUNK_GPU_RENDERABLE_BUILDER