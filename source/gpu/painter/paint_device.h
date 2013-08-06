#ifndef _H_PUNK_PAINT_DEVICE
#define _H_PUNK_PAINT_DEVICE

#include "../../config.h"

namespace Gpu
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
	class PUNK_ENGINE_API PaintDevice
	{
	public:
		PaintDevice();
		virtual ~PaintDevice();

		PaintEngine* GetPaintEngine();
		int GetWidth() const;
		int GetHeight() const;

	protected:
		void SetWidth(int width);
		void SetHeight(int height);
		void SetPaintEngine(PaintEngine* value);

	private:
		int m_width;
		int m_height;
		PaintEngine* m_engine;

		//	no copy
		PaintDevice(const PaintDevice&);
		PaintDevice& operator = (const PaintDevice&);
	};

	inline int PaintDevice::GetWidth() const
	{
		return m_width;
	}

	inline int PaintDevice::GetHeight() const
	{
		return m_height;
	}

	inline void PaintDevice::SetWidth(int width)
	{
		m_width = width;
	}

	inline void PaintDevice::SetHeight(int height)
	{
		m_height = height;
	}

	inline PaintEngine* PaintDevice::GetPaintEngine()
	{
		return m_engine;
	}

	inline void PaintDevice::SetPaintEngine(PaintEngine* value)
	{
		m_engine = value;
	}
}

#endif	//	_H_PUNK_PAINT_DEVICE
