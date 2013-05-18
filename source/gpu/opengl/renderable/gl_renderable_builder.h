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
    //class Frame;

	struct RenderableBuilderImpl
	{
		RenderableBuilderImpl(VideoDriver* driver);

		void Begin(const PrimitiveType& value);
		void Vertex3f(float x, float y, float z);
		void Vertex3fv(const float* value);
        void Color3f(float r, float g, float b);
		void Color3fv(const float* value);
        void Color3fv(const Math::vec3& value);
		void TexCoord2f(float x, float y);
		void TexCoord2fv(const float* value);
		void TexCoord2fv(const Math::vec2& value);
		void End();

		void ValidateBegin();
		void ValidateEnd();
        void ValidateDraw();

		VideoDriver* m_driver;
        //Frame* m_current_frame;

		std::vector<Math::vec4> m_vertex;
		std::vector<Math::vec4> m_color;
		std::vector<Math::vec4> m_normal;
		std::vector<Math::vec4> m_texcoord;

        bool m_begin_active;

		GLenum m_primitive_type;
		PrimitiveType m_high_level_type;

		Renderable* BuildVertexBufferP(const std::vector<Math::vec4>& position);
		Renderable* BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord);
		Renderable* BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal);
		Renderable* BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord);

        Renderable* ToRenderable();
	};
}

#endif	//	_H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER
