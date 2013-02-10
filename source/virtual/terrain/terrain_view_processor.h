#ifndef _H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR
#define _H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR

#include "../../config.h"
#include "../../system/streaming/data_processor.h"

namespace GPU { namespace OpenGL { class Texture2D; } }

namespace Virtual
{
	struct TerrainViewProcessorDesc
	{
		int m_view_size;
		GPU::OpenGL::Texture2D* m_height_map;
		//	DMA pointer to the data
		void* m_device_ptr;

		void(*OnEnd)(void*);
		void* m_on_end_data;
	};

	class PUNK_ENGINE TerrainViewProcessor : public System::AbstractDataProcessor
	{
	public:
		/**
		*	Nothing to destroy
		*/
		virtual ~TerrainViewProcessor() {};
		/**
		*	This do nothing, because we have a texture to copy data in
		*/
		virtual System::StreamingStepResult LockDeviceObject();
		/**
		*	This do nothing 
		*/
		virtual System::StreamingStepResult UnlockDeviceObject();
		/**
		*	This can perform data convertion, if float textures
		*	are not supported
		*/
		virtual System::StreamingStepResult Process(void* data, unsigned size);
		/**
		*	Data is copied to the texture here
		*/
		virtual System::StreamingStepResult CopyToResource();

		virtual System::StreamingStepResult SetResourceError();

		/**
		*	Constructor receives a pointer to the texture to process data in
		*	Texture should be created and valid
		*/
		TerrainViewProcessor(const TerrainViewProcessorDesc& desc);

	private:
		TerrainViewProcessorDesc m_desc;
		void* m_data;
		unsigned m_size;
	};
}
#endif	//	_H_PUNK_VIRTUAL_TERRAIN_VIEW_PROCESSOR