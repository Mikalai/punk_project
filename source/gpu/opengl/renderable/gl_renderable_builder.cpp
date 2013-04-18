#include "gl_renderable_builder.h"
#include "gl_primitive_type.h"
#include "../error/module.h"
#include "../../common/renderable.h"
#include "../../common/vertex.h"
#include "../../common/vertex_component.h"
#include "../renderable/module.h"
#include "../driver/module.h"
#include "../render/gl_frame.h"

namespace GPU
{
	RenderableBuilderImpl::RenderableBuilderImpl(VideoDriver* driver)
		: m_driver(driver)
		, m_current_frame(nullptr)
	{}

	template<typename VertexType>
	Renderable* Cook(GLenum type, const std::vector<VertexType>& buffer)
	{		
		if (type  == GL_POINTS)
		{
			std::unique_ptr<OpenGL::Points<VertexType>> result(new OpenGL::Points<VertexType>());
			result->Cook(buffer);
			return result.release();
		}
		else if (type == GL_LINES)
		{
			std::unique_ptr<OpenGL::Lines<VertexType>> result(new OpenGL::Lines<VertexType>());
			result->Cook(buffer);
			return result.release();
		}
		else if (type == GL_TRIANGLES)
		{
			std::unique_ptr<OpenGL::Triangles<VertexType>> result(new OpenGL::Triangles<VertexType>());
			result->Cook(buffer);
			return result.release();
		}
		else
			throw OpenGL::OpenGLInvalidValueException(L"Unsupported primitive type");
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferP(const std::vector<Math::vec4>& position)
	{
		typedef Vertex<VertexComponent::Position> VertexType;
		std::vector<VertexType> vb(position.size());
		for (auto& p : position)
		{
			VertexType v;
			v.m_position = p;
			vb.push_back(v);
		}
		
		return Cook<VertexType>(m_primitive_type, vb);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color)
	{
		if (position.size() != color.size())
			throw OpenGL::OpenGLInvalidValueException(L"Position and color buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Color> VertexType;
		std::vector<VertexType> vb(position.size());
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
		
		return Cook<VertexType>(m_primitive_type, vb);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord)
	{
		if (position.size() != texcoord.size())
			throw OpenGL::OpenGLInvalidValueException(L"Position and texture buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb(position.size());
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
		
		return Cook<VertexType>(m_primitive_type, vb);
	}
		
	Renderable* RenderableBuilderImpl::BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color)
	{
		if (position.size() != texcoord.size() || position.size() != color.size())
			throw OpenGL::OpenGLInvalidValueException(L"Position, texture or color buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb(position.size());
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
		
		return Cook<VertexType>(m_primitive_type, vb);
	}

	Renderable* RenderableBuilderImpl::BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal)
	{
		if (position.size() != normal.size())
			throw OpenGL::OpenGLInvalidValueException(L"Position and normal buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Normal> VertexType;
		std::vector<VertexType> vb(position.size());
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
		
		return Cook<VertexType>(m_primitive_type, vb);
	}
		
	Renderable* RenderableBuilderImpl::BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord)
	{
		if (position.size() != texcoord.size() || position.size() != normal.size())
			throw OpenGL::OpenGLInvalidValueException(L"Position, texture or normal buffer has different size");

		typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> VertexType;
		std::vector<VertexType> vb(position.size());
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
		
		return Cook<VertexType>(m_primitive_type, vb);
	}

	void RenderableBuilderImpl::Begin(const PrimitiveType& value)
	{
		ValidateBegin();
		m_primitive_type = OpenGL::PrimitiveTypeToOpenGL(value);

		m_current_frame = m_driver->BeginFrame();
	}

	void RenderableBuilderImpl::Vertex3f(float x, float y, float z)
	{
		m_vertex.push_back(Math::vec4(x, y, z, 1));
	}
	
	void RenderableBuilderImpl::Vertex3fv(float* value)
	{
		m_vertex.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}
	
	void RenderableBuilderImpl::End()
	{
		ValidateEnd();

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
			throw OpenGL::OpenGLInvalidValueException(L"Unsupported vertex type in RenderableBuilder");

		//m_current_frame->BeginRendering();
		//m_current_frame->Render(renderable);
		//m_current_frame->EndRendering();		
	}

	void RenderableBuilderImpl::ValidateBegin()
	{
	}

	void RenderableBuilderImpl::ValidateEnd()
	{
	}
}