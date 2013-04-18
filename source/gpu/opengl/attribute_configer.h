#ifndef _H_PUNK_OPENGL_CONFIGER
#define _H_PUNK_OPENGL_CONFIGER

//	Common utility stuff
#include "../common/module.h"
#include "error/module.h"
#include "gl/module.h"
//	Math
#include "../../math/vec4.h"
#include "../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<typename VertexType> class AttributeConfiger;

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position>>
		{
			typedef Vertex<VertexComponent::Position> CurrentVertex;			
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Texture0>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Texture0> CurrentVertex;			
		public:
			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Color>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Color> CurrentVertex;			
		public:
			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position,
			VertexComponent::Normal>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal> CurrentVertex;
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Texture0>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> CurrentVertex;
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Color, 
			VertexComponent::Texture0>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0> CurrentVertex;
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Texture0, 
			VertexComponent::Flag>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0, VertexComponent::Flag> CurrentVertex;
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position,
			VertexComponent::Texture0,
			VertexComponent::Flag,
			VertexComponent::Color>>
		{
			typedef Vertex<VertexComponent::Position,
				VertexComponent::Texture0,
				VertexComponent::Flag,
				VertexComponent::Color> CurrentVertex;			

		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position,
			VertexComponent::Normal,
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
			VertexComponent::Texture0>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Tangent, VertexComponent::Bitangent, VertexComponent::Texture0> CurrentVertex;
		public:

			AttributeConfiger(int64_t available);
		};

		template<> 
		class AttributeConfiger<
			Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
			VertexComponent::Texture0, 
			VertexComponent::BoneID,
			VertexComponent::BoneWeight>>
		{
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Tangent, VertexComponent::Bitangent, VertexComponent::Texture0, VertexComponent::BoneID, VertexComponent::BoneWeight> CurrentVertex;

		public:

			AttributeConfiger(int64_t available);
		};
	}
}

#endif