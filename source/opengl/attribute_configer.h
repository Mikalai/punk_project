#ifndef _H_PUNK_OPENGL_CONFIGER
#define _H_PUNK_OPENGL_CONFIGER

//	Common utility stuff
#include "../utility/model/vertex.h"

//	Math
#include "../math/vec4.h"

//	OpenGL
#include "extensions.h"

namespace OpenGL
{
	template<int U> class AttributeConfiger;

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION };
	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;

			if (components == SUPPORTED)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE };
	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;

			if (components == Utility::COMPONENT_POSITION)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL };
	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;

			if (components == Utility::COMPONENT_POSITION)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE };
	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;
			int size = sizeof(CurrentVertex);
			if (components == Utility::COMPONENT_POSITION)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	texture
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	texture
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE };

	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;

			if (components == Utility::COMPONENT_POSITION)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");				
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION
				|Utility::COMPONENT_NORMAL
				|Utility::COMPONENT_TANGENT
				|Utility::COMPONENT_BITANGENT
				|Utility::COMPONENT_TEXTURE))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	tangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	bitangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(2);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(3);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};

	template<> class AttributeConfiger<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BONE_WEIGHT|Utility::COMPONENT_BONE_ID>
	{
		typedef Utility::Vertex<Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BONE_WEIGHT|Utility::COMPONENT_BONE_ID> CurrentVertex;
		enum Code { SUPPORTED = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BONE_WEIGHT|Utility::COMPONENT_BONE_ID };

	public:

		AttributeConfiger(Utility::VertexAttributes available)
		{
			Utility::VertexAttributes components = SUPPORTED & available;

			if (components == (Utility::COMPONENT_POSITION
				|Utility::COMPONENT_BONE_WEIGHT
				|Utility::COMPONENT_BONE_ID))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION
				|Utility::COMPONENT_TEXTURE
				|Utility::COMPONENT_BONE_WEIGHT
				|Utility::COMPONENT_BONE_ID))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION
				|Utility::COMPONENT_NORMAL
				|Utility::COMPONENT_BONE_WEIGHT
				|Utility::COMPONENT_BONE_ID))
			{	
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION
				|Utility::COMPONENT_NORMAL
				|Utility::COMPONENT_TEXTURE
				|Utility::COMPONENT_BONE_WEIGHT
				|Utility::COMPONENT_BONE_ID))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(1*4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BONE_WEIGHT|Utility::COMPONENT_BONE_ID))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(1*4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	tangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	bitangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(2);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(3);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				out_error() << "Vertex do not support such render context" << std::endl;
			}
		}
	};
}

#endif