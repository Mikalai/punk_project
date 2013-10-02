#include "attribute_configer.h"
#include "../common/module.h"
#include "error/module.h"
#include "gl/module.h"
#include "../../math/vec4.h"

namespace Gpu
{
	namespace OpenGL
	{
		AttributeConfiger<Vertex<VertexComponent::Position>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Texture0>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
            int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{					
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture_0
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Color>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{				
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{					
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	color
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Color::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<VertexComponent::Position, VertexComponent::Normal>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Texture0>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();

			int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Color, 
			VertexComponent::Texture0>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();

			int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal,
			VertexComponent::Texture0, 
			VertexComponent::Flag>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0, VertexComponent::Flag>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Flag::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::FlagOffset());	//	flag
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position,
			VertexComponent::Texture0,
			VertexComponent::Flag,
			VertexComponent::Color>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;
			int size = sizeof(CurrentVertex);
			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, size, (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set POSITION vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set POSITION vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	color
				ValidateOpenGL(L"Unable to set COLOR vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	color
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Color::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::ColorOffset());	//	color
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Flag::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::FlagOffset());	//	flag
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
			VertexComponent::Texture0>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture_0

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
			{	
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture_0

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");				
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Tangent
				, VertexComponent::Bitangent
				, VertexComponent::Texture0>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset());	//	normal

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset());	//	tangent

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset());	//	bitangent

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset());	//	texture_0

				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Normal::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Tangent::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Bitangent::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::Texture0::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else
				throw OpenGLException(L"Vertex do not support such render context");
		}

		AttributeConfiger<Vertex<
			VertexComponent::Position, 
			VertexComponent::Normal, 
			VertexComponent::Tangent, 
			VertexComponent::Bitangent, 
			VertexComponent::Texture0, 
			VertexComponent::BoneID,
			VertexComponent::BoneWeight>>::AttributeConfiger(int64_t available)
		{
			static const int64_t Code = CurrentVertex::Value();
			int64_t components = Code & available;

			if (components == Vertex<VertexComponent::Position
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
				glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset());	//	position
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset());	//	bone_id
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE
					, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset());	//	bone_weight
				ValidateOpenGL(L"Unable to set vertex attrib pointer vao");

				glEnableVertexAttribArray(VertexComponent::Position::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::BoneID::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot());
				ValidateOpenGL(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{	
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
			}
			else if (components == Vertex<VertexComponent::Position
				, VertexComponent::Normal
				, VertexComponent::Tangent
				, VertexComponent::Bitangent
				, VertexComponent::Texture0
				, VertexComponent::BoneID
				, VertexComponent::BoneWeight>::Value())
			{
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset()));	//	tangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset()));	//	bitangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneID::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneIDOffset()));	//	bone_id
                GL_CALL(glVertexAttribPointer(VertexComponent::BoneWeight::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BoneWeightOffset()));	//	bone_weight

                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Tangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Bitangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneID::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::BoneWeight::Slot()));
            }
            else if (components == Vertex<VertexComponent::Position
                                    , VertexComponent::Normal
                                    , VertexComponent::Tangent
                                    , VertexComponent::Bitangent
                                    , VertexComponent::Texture0>::Value())
            {
                GL_CALL(glVertexAttribPointer(VertexComponent::Position::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::PositionOffset()));	//	position
                GL_CALL(glVertexAttribPointer(VertexComponent::Normal::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::NormalOffset()));	//	normal
                GL_CALL(glVertexAttribPointer(VertexComponent::Tangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::TangentOffset()));	//	tangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Bitangent::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::BitangentOffset()));	//	bitangent
                GL_CALL(glVertexAttribPointer(VertexComponent::Texture0::Slot(), 4, GL_FLOAT, GL_FALSE, sizeof(CurrentVertex), (void*)CurrentVertex::Texture0Offset()));	//	texture_0
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Position::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Normal::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Tangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Bitangent::Slot()));
                GL_CALL(glEnableVertexAttribArray(VertexComponent::Texture0::Slot()));
            }
            else
                throw OpenGLException(L"Vertex do not support such render context");
        }
    }
}
