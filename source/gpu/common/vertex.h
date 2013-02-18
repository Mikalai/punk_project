#ifndef _H_PUNK_GPU_VERTEX
#define _H_PUNK_GPU_VERTEX

#include "../../config.h"
#include "../../math/vec4.h"
#include "vertex_component.h"

namespace GPU
{
	template<int VertexType> struct Vertex;

	template<> struct Vertex<
		COMPONENT_POSITION> 
	{	
		Math::vec4 m_position;		
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_NORMAL>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_NORMAL|
		COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_NORMAL|
		COMPONENT_TANGENT|
		COMPONENT_BITANGENT|
		COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_NORMAL|
		COMPONENT_TANGENT|
		COMPONENT_BITANGENT|
		COMPONENT_TEXTURE|
		COMPONENT_BONE_ID|
		COMPONENT_BONE_WEIGHT>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;
		Math::vec4 m_bones_id;
		Math::vec4 m_bone_weights;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_NORMAL|
		COMPONENT_TEXTURE|
		COMPONENT_FLAG>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;
		Math::vec4 m_flag;
	};

	template<> struct Vertex<
		COMPONENT_POSITION|
		COMPONENT_COLOR|
		COMPONENT_TEXTURE|
		COMPONENT_FLAG>
	{
		Math::vec4 m_position;		
		Math::vec4 m_texture0;
		Math::vec4 m_flag;
		Math::vec4 m_color;
	};
}

#endif	//	_H_PUNK_GPU_VERTEX