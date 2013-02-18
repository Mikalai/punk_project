#ifndef _H_PUNK_OPENGL_CONFIGER
#define _H_PUNK_OPENGL_CONFIGER

//	Common utility stuff
#include "../common/module.h"
#include "error/module.h"
#include "gl/module.h"
//	Math
#include "../../math/vec4.h"

namespace GPU
{
	namespace OpenGL
	{
		template<int U> class AttributeConfiger;

		template<> class AttributeConfiger<COMPONENT_POSITION>
		{
			typedef Vertex<COMPONENT_POSITION> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;

				if (components == SUPPORTED)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_TEXTURE>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_TEXTURE> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_TEXTURE };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;

				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_TEXTURE))
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
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_NORMAL>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_NORMAL> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_NORMAL };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;

				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL))
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
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;
				int size = sizeof(CurrentVertex);
				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, size, (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_TEXTURE))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE))
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
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_FLAG>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_FLAG> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_FLAG };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;
				int size = sizeof(CurrentVertex);
				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, size, (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_TEXTURE))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_FLAG))
				{	
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(1*4*sizeof(float)));	//	normal
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	texture
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	bone_weight
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(1);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(4);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_COLOR|COMPONENT_TEXTURE|COMPONENT_FLAG>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_COLOR|COMPONENT_TEXTURE|COMPONENT_FLAG> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_COLOR|COMPONENT_TEXTURE|COMPONENT_FLAG };
		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;
				int size = sizeof(CurrentVertex);
				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, size, (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set POSITION vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_COLOR))
				{	
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set POSITION vertex attrib pointer vao");
					glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	color
					CHECK_GL_ERROR(L"Unable to set COLOR vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(1);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_TEXTURE))
				{	
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	texture
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(4);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_COLOR|COMPONENT_TEXTURE))
				{	
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	texture
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	color
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(1);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(4);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_COLOR|COMPONENT_TEXTURE|COMPONENT_FLAG))
				{	
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(3*4*sizeof(float)));	//	color
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(4*sizeof(float)));	//	texture
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)(2*4*sizeof(float)));	//	flag
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(1);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
					glEnableVertexAttribArray(4);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE };

		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;

				if (components == COMPONENT_POSITION)
				{
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)0);	//	position
					CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
					glEnableVertexAttribArray(0);
					CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				}
				else if (components == (COMPONENT_POSITION|COMPONENT_TEXTURE))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE))
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
				else if (components == (COMPONENT_POSITION
					|COMPONENT_NORMAL
					|COMPONENT_TANGENT
					|COMPONENT_BITANGENT
					|COMPONENT_TEXTURE))
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
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};

		template<> class AttributeConfiger<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID>
		{
			typedef Vertex<COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID> CurrentVertex;
			enum Code { SUPPORTED = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID };

		public:

			AttributeConfiger(VertexAttributes available)
			{
				VertexAttributes components = SUPPORTED & available;

				if (components == (COMPONENT_POSITION
					|COMPONENT_BONE_WEIGHT
					|COMPONENT_BONE_ID))
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
				else if (components == (COMPONENT_POSITION
					|COMPONENT_TEXTURE
					|COMPONENT_BONE_WEIGHT
					|COMPONENT_BONE_ID))
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
				else if (components == (COMPONENT_POSITION
					|COMPONENT_NORMAL
					|COMPONENT_BONE_WEIGHT
					|COMPONENT_BONE_ID))
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
				else if (components == (COMPONENT_POSITION
					|COMPONENT_NORMAL
					|COMPONENT_TEXTURE
					|COMPONENT_BONE_WEIGHT
					|COMPONENT_BONE_ID))
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
				else if (components == (COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TANGENT|COMPONENT_BITANGENT|COMPONENT_TEXTURE|COMPONENT_BONE_WEIGHT|COMPONENT_BONE_ID))
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
					throw OpenGLException(L"Vertex do not support such render context");
			}
		};
	}
}

#endif