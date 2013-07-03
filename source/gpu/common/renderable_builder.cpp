#include <memory>
#include "renderable_builder.h"
#include "primitive_type.h"
#include "primitives/module.h"

namespace GPU
{
	class VideoDriver;
	class Renderable;

	struct RenderableBuilderImpl
	{
		RenderableBuilderImpl(VideoDriver* driver);

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

		PrimitiveType m_primitive_type;
		PrimitiveType m_high_level_type;

		Renderable* BuildVertexBufferP(const std::vector<Math::vec4>& position);
		Renderable* BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord);
		Renderable* BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color);
		Renderable* BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal);
		Renderable* BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord);

		Renderable* ToRenderable();
	};

	RenderableBuilderImpl::RenderableBuilderImpl(VideoDriver* driver)
		: m_driver(driver)
		, m_begin_active(false)
	{}

	template<typename VertexType>
	Renderable* Cook(PrimitiveType type, const std::vector<VertexType>& buffer, VideoDriver* driver)
	{
		if (type  == PrimitiveType::POINTS)
		{
			std::unique_ptr<Points<VertexType>> result(new Points<VertexType>(driver));
			result->Cook(buffer);
			return result.release();
		}
		else if (type == PrimitiveType::LINES)
		{
			std::unique_ptr<Lines<VertexType>> result(new Lines<VertexType>(driver));
			result->Cook(buffer);
			return result.release();
		}
		else if (type == PrimitiveType::TRIANGLES)
		{
			std::unique_ptr<Triangles<VertexType>> result(new Triangles<VertexType>(driver));
			result->Cook(buffer);
			return result.release();
		}
		else
			throw System::PunkException(L"Unsupported primitive type");
	}

	template<typename Vertex>
	void ModifyVertexInput(std::vector<Vertex>& inout, PrimitiveType src_type)
	{
		if (src_type == PrimitiveType::QUADS)
			QuadsToTriangles(inout, src_type);
		else if (src_type == PrimitiveType::POLYGON)
			PolygonToTriangles(inout, src_type);
	}

	template<typename Vertex>
	void QuadsToTriangles(std::vector<Vertex>& inout, PrimitiveType src_type)
	{
		std::vector<Vertex> in = inout;
		if (src_type == PrimitiveType::QUADS)
		{
			if (in.size() % 4 != 0)
				throw System::PunkException(L"Invalid vertex buffer. Count of vertex is not devided by 4");

			inout.clear();

			for (size_t i = 0; i != in.size(); i += 4)
			{
				const Vertex& v1 = in[i];
				const Vertex& v2 = in[i+1];
				const Vertex& v3 = in[i+2];
				const Vertex& v4 = in[i+3];

				inout.push_back(v1);
				inout.push_back(v2);
				inout.push_back(v3);

				inout.push_back(v3);
				inout.push_back(v4);
				inout.push_back(v1);
			}
		}
	}

	template<typename Vertex>
	void PolygonToTriangles(std::vector<Vertex>& inout, PrimitiveType src_type)
	{
		std::vector<Vertex> in = inout;
		if (src_type == PrimitiveType::POLYGON)
		{
			if (in.size() < 3)
				throw System::PunkException(L"Invalid vertex buffer. Not enough points");
			inout.clear();

			for (size_t i = 1; i != in.size() - 1; ++i)
			{
				inout.push_back(in[0]);
				inout.push_back(in[i]);
				inout.push_back(in[i+1]);
			}
		}
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferP(const std::vector<Math::vec4>& position)
	{
		typedef Vertex<VertexComponent::Position> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		for (auto& p : position)
		{
			VertexType v;
			v.m_position = p;
			vb.push_back(v);
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color)
	{
		if (position.size() != color.size())
			throw System::PunkException(L"Position and color buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Color> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		auto p_it = position.begin();
		auto c_it = color.begin();
		while (p_it != position.end() && c_it != color.end())
		{
			VertexType v;
			v.m_position = *p_it;
			v.m_color = *c_it;
			vb.push_back(v);

			++p_it;
			++c_it;
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord)
	{
		if (position.size() != texcoord.size())
			throw System::PunkException(L"Position and texture buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		auto p_it = position.begin();
		auto t_it = texcoord.begin();
		while (p_it != position.end() && t_it != texcoord.end())
		{
			VertexType v;
			v.m_position = *p_it;
			v.m_texture0 = *t_it;
			vb.push_back(v);

			++p_it;
			++t_it;
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color)
	{
		if (position.size() != texcoord.size() || position.size() != color.size())
			throw System::PunkException(L"Position, texture or color buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		auto p_it = position.begin();
		auto t_it = texcoord.begin();
		auto c_it = color.begin();
		while (p_it != position.end() && t_it != texcoord.end() && c_it != color.end())
		{
			VertexType v;
			v.m_position = *p_it;
			v.m_texture0 = *t_it;
			v.m_color = *c_it;
			vb.push_back(v);

			++p_it;
			++t_it;
			++c_it;
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal)
	{
		if (position.size() != normal.size())
			throw System::PunkException(L"Position and normal buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Normal> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		auto p_it = position.begin();
		auto n_it = normal.begin();
		while (p_it != position.end() && n_it != normal.end())
		{
			VertexType v;
			v.m_position = *p_it;
			v.m_normal = *n_it;
			vb.push_back(v);

			++p_it;
			++n_it;
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord)
	{
		if (position.size() != texcoord.size() || position.size() != normal.size())
			throw System::PunkException(L"Position, texture or normal buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb;
		vb.reserve(position.size());
		auto p_it = position.begin();
		auto t_it = texcoord.begin();
		auto n_it = normal.begin();
		while (p_it != position.end() && t_it != texcoord.end() && n_it != normal.end())
		{
			VertexType v;
			v.m_position = *p_it;
			v.m_texture0 = *t_it;
			v.m_normal = *n_it;
			vb.push_back(v);

			++p_it;
			++t_it;
			++n_it;
		}

		ModifyVertexInput(vb, m_high_level_type);
		return Cook<VertexType>(m_primitive_type, vb, m_driver);
	}

	void RenderableBuilderImpl::Begin(const PrimitiveType& value)
	{
		ValidateBegin();
		m_high_level_type = value;
		//	Low level apis do not support quads -> triangles
		if (value == PrimitiveType::QUADS)
			m_primitive_type = PrimitiveType::TRIANGLES;
		else
			m_primitive_type = value;
		//m_current_frame = m_driver->BeginFrame();
	}

	void RenderableBuilderImpl::Vertex3f(float x, float y, float z)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(x, y, z, 1));
	}

	void RenderableBuilderImpl::Vertex3fv(const float* value)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

	void RenderableBuilderImpl::Vertex3fv(const Math::vec3 &value)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

	void RenderableBuilderImpl::Color3f(float r, float g, float b)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(r, g, b, 1.0f));
	}

	void RenderableBuilderImpl::Color3fv(const float* value)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

	void RenderableBuilderImpl::Color3fv(const Math::vec3& value)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(value, 1));
	}

	void RenderableBuilderImpl::TexCoord2f(float x, float y)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(x, y, 0, 0));
	}

	void RenderableBuilderImpl::TexCoord2fv(const float* value)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(value[0], value[1], 0, 0));
	}

	void RenderableBuilderImpl::TexCoord2fv(const Math::vec2& value)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(value[0], value[1], 0, 0));
	}

	void RenderableBuilderImpl::Normal3f(float x, float y, float z)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(x, y, z, 0));
	}

	void RenderableBuilderImpl::Normal3fv(const float* value)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(value[0], value[1], value[2], 0));
	}

	void RenderableBuilderImpl::Normal3fv(const Math::vec3& value)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(value[0], value[1], value[2], 0));
	}

	void RenderableBuilderImpl::End()
	{
		ValidateEnd();

		//m_current_frame->BeginRendering();
		//m_current_frame->Render(renderable);
		//m_current_frame->EndRendering();
	}

	void RenderableBuilderImpl::ValidateBegin()
	{
		if (m_begin_active)
			throw System::PunkException(L"Begin has been already called");
		m_begin_active = true;
	}

	void RenderableBuilderImpl::ValidateEnd()
	{
		if (!m_begin_active)
			throw System::PunkException(L"Failed to perform End(), because begin was not called");
		m_begin_active = false;
	}

	void RenderableBuilderImpl::ValidateDraw()
	{
		if (!m_begin_active)
			throw System::PunkException(L"Failed to draw, because Begin() was not called");
	}

	Renderable* RenderableBuilderImpl::ToRenderable()
	{
		int64_t c = 0;
		c |= m_vertex.empty() ? 0 : VertexComponent::Position::Value();
		c |= m_color.empty() ? 0 : VertexComponent::Color::Value();
		c |= m_normal.empty() ? 0 : VertexComponent::Normal::Value();
		c |= m_texcoord.empty() ? 0 : VertexComponent::Texture0::Value();

		Renderable* renderable;
		if (c == Vertex<VertexComponent::Position>::Value())
			renderable = BuildVertexBufferP(m_vertex);
		else if (c == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			renderable = BuildVertexBufferPC(m_vertex, m_color);
		else if (c == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			renderable = BuildVertexBufferPT(m_vertex, m_texcoord);
		else if (c == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
			renderable = BuildVertexBufferPTC(m_vertex, m_texcoord, m_color);
		else if (c == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			renderable = BuildVertexBufferPN(m_vertex, m_normal);
		else if (c == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			renderable = BuildVertexBufferPNT0(m_vertex, m_normal, m_texcoord);
		else
			throw System::PunkException(L"Unsupported vertex type in RenderableBuilder");
		return renderable;
	}

    bool RenderableBuilderImpl::IsValid() const
    {
        return !m_vertex.empty();
    }

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

	void RenderableBuilder::Vertex3fv(const float* value)
	{
		impl->Vertex3fv(value);
	}

	void RenderableBuilder::Vertex3fv(const Math::vec3 &value)
	{
		impl->Vertex3fv(value);
	}

	void RenderableBuilder::Color3f(float r, float g, float b)
	{
		impl->Color3f(r, g, b);
	}

	void RenderableBuilder::Color3fv(const Math::vec3 &value)
	{
		impl->Color3fv(value);
	}

	void RenderableBuilder::Color3fv(const float *value)
	{
		impl->Color3fv(value);
	}

	void RenderableBuilder::TexCoord2f(float x, float y)
	{
		impl->TexCoord2f(x, y);
	}

	void RenderableBuilder::TexCoord2fv(const float* value)
	{
		impl->TexCoord2fv(value);
	}

	void RenderableBuilder::TexCoord2fv(const Math::vec2& value)
	{
		impl->TexCoord2fv(value);
	}

	Renderable* RenderableBuilder::ToRenderable()
	{
		return impl->ToRenderable();
	}

    bool RenderableBuilder::IsValid() const
    {
        return impl->IsValid();
    }

	void RenderableBuilder::Normal3f(float x, float y, float z)
	{
		impl->Normal3f(x, y, z);
	}

	void RenderableBuilder::Normal3fv(const float* value)
	{
		impl->Normal3fv(value);
	}

	void RenderableBuilder::Normal3fv(const Math::vec3& value)
	{
		impl->Normal3fv(value);
	}
}
