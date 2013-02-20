#ifndef _H_PUNK_PAINT_DEVICE
#define _H_PUNK_PAINT_DEVICE

namespace GPU
{
	class PaintEngine;
	/**
	*	This is used to represent a surface that can be filled
	*	with drawing data. To perform draw information transfition
	*	to the device PaintEngine is used.
	*	This should be implemented by low level API
	*
	*	
	*/
	class PaintDevice
	{
	public:
		virtual PaintEngine* GetPaintEngine() = 0;
	};
}

#endif	//	_H_PUNK_PAINT_DEVICE