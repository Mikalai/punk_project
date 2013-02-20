#ifndef _H_PUNK_PAINT_ENGINE
#define _H_PUNK_PAINT_ENGINE

namespace GPU
{
	class PaintDevice;

	/**
	*	This is an interface for Painter. This should be reimplemented
	*	using OpenGL or other low level api
	*	Paint engine performs its rendering into PaintDevice
	*/
	class PaintEngine
	{
	public:
		virtual PaintDevice* GetPaintDevice() = 0;
	};
}

#endif	//	_H_PUNK_PAINT_ENGINE