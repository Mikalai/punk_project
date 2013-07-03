#ifndef _H_PUNK_GPU_RENDERABLE_BUILDER
#define _H_PUNK_GPU_RENDERABLE_BUILDER

#include "../../config.h"
#include "renderable.h"

namespace Math
{
	class vec4;
	class vec3;
	class vec2;
}

namespace GPU
{
	enum class PrimitiveType;

	struct RenderableBuilderImpl;

	class VideoDriver;

	class PUNK_ENGINE_API RenderableBuilder final
	{
	public:
		RenderableBuilder(VideoDriver* driver);
		~RenderableBuilder();

		void Begin(const PrimitiveType& value);
		void Vertex3f(float x, float y, float z);
		void Vertex3fv(const float* value);
		void Vertex3fv(const Math::vec3& value);
		void Color3f(float r, float g, float b);
		void Color3fv(const float* value);
		void Color3fv(const Math::vec3& value);
		void TexCoord2f(float x, float y);
		void TexCoord2fv(const float* value);
		void TexCoord2fv(const Math::vec2& value);
		void Normal3f(float x, float y, float z);
		void Normal3fv(const float* value);
		void Normal3fv(const Math::vec3& value);
		void End();

        bool IsValid() const;

		/**
		 * @brief ToRenderable converts internal data stored to the renderable entity
		 * @return Pointer to the renderable. Should be destroyed somewhere
		 */
		Renderable* ToRenderable();

		RenderableBuilderImpl* impl;

	private:
		RenderableBuilder(const RenderableBuilder&);
		RenderableBuilder(const RenderableBuilder&&);
		RenderableBuilder& operator = (const RenderableBuilder&);
		RenderableBuilder& operator = (const RenderableBuilder&&);
	};
}

#endif	//	_H_PUNK_GPU_RENDERABLE_BUILDER
