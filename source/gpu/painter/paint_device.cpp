#include "paint_device.h"
#include "paint_engine.h"

namespace GPU
{
	PaintDevice::PaintDevice()
		: m_engine(nullptr)
	{}

	PaintDevice::~PaintDevice()
	{
		delete m_engine;
		m_engine = nullptr;
	}
}
