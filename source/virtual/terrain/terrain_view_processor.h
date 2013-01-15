#ifndef _H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR
#define _H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR

#include "../../config.h"
#include "../../system/streaming/data_processor.h"

namespace OpenGL { class Texture2D; }

namespace Virtual
{
	class PUNK_ENGINE TerrainViewProcessor : public System::AbstractDataProcessor
	{
	public:
		/**
		*	Constructor receives a pointer to the texture to process data in
		*	Texture should be created and valid
		*/
		TerrainViewProcessor(OpenGL::Texture2D* height_map);
		/**
		*	Nothing to destroy
		*/
		virtual ~TerrainViewProcessor() {};
		/**
		*	This do nothing, because we have a texture to copy data in
		*/
		virtual unsigned LockDeviceObject();
		/**
		*	This do nothing 
		*/
		virtual unsigned UnlockDeviceObject();
		/**
		*	This can perform data convertion, if float textures
		*	are not supported
		*/
		virtual unsigned Process(void* data, unsigned size);
		/**
		*	Data is copied to the texture here
		*/
		virtual unsigned CopyToResource();

		virtual unsigned SetResourceError();
	private:
		void* m_data;
		unsigned m_size;
		OpenGL::Texture2D* m_height_map;
	};
}
#endif	//	_H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR