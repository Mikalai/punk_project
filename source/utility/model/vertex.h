#ifndef _H_PUNK_UTILITY_VERTEX
#define _H_PUNK_UTILITY_VERTEX

#include "../config.h"
#include "../math/vec4.h"
#include "vertex_component.h"

namespace Utility
{
	template<int VertexType> struct Vertex;

	template<> struct Vertex<
		Utility::COMPONENT_POSITION> 
	{	
		Math::vec4 m_position;		
	};

	template<> struct Vertex<
		Utility::COMPONENT_POSITION|
		Utility::COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
	};

	template<> struct Vertex<
		Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TANGENT|
		Utility::COMPONENT_BITANGENT|
		Utility::COMPONENT_TEXTURE>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;
	};

	template<> struct Vertex<
		Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TANGENT|
		Utility::COMPONENT_BITANGENT|
		Utility::COMPONENT_TEXTURE|
		Utility::COMPONENT_BONE_ID|
		Utility::COMPONENT_BONE_WEIGHT>
	{
		Math::vec4 m_position;
		Math::vec4 m_normal;
		Math::vec4 m_tangent;
		Math::vec4 m_bitangent;
		Math::vec4 m_texture0;
		Math::vec4 m_bones_id;
		Math::vec4 m_bone_weights;
	};
}

#endif