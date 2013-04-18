#ifndef _H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER
#define _H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER

#include <vector>
#include "../../common/renderable_builder.h"
#include "../../../math/vec4.h"
#include "../gl/module.h"

namespace GPU
{
	class VideoDriver;
	class Renderable;
	class Frame;

	struct RenderableBuilderImpl
	{
		RenderableBuilderImpl(VideoDriver* driver);

		void Begin(const PrimitiveType& value);
		void Vertex3f(float x, float y, float z);
		void Vertex3fv(float* value);
		void End();

		void ValidateBegin();
		void ValidateEnd();

		VideoDriver* m_driver;
		Frame* m_current_frame;

		std::vector<Math::vec4> m_vertex;
		std::vector<Math::vec4> m_color;
		std::vector<Math::vec4> m_normal;
		std::vector<Math::vec4> m_texcoord;

		GLenum m_primitive_type;

		Renderable* BuildVertexBufferP(const std::vector<Math::vec4>& position);
		Renderable* BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord);
		Renderable* BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal);
		Renderable* BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord);

	};
}

#endif	//	_H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER