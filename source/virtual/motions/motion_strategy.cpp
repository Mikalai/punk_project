#include "motion_strategy.h"
#include "../../system/logger.h"

namespace Virtual
{
	MotionStrategy::MotionStrategy()
		: System::Object()
		, m_transform(0)
		, m_motion_type(MotionStrategyType::MOTION_STRATEGY_TYPE_NONE)
	{}

	MotionStrategy::~MotionStrategy()
	{}

	bool MotionStrategy::Save(std::ostream& stream) const
	{
		if (!System::Object::Save(stream))
		{
			out_error() << "Can't save motion strategy" << std::endl;
			return false;
		}

		stream.write((char*)&m_motion_type, sizeof(m_motion_type));

		return true;
	}

	bool MotionStrategy::Load(std::istream& stream)
	{
		if (!System::Object::Load(stream))
		{
			out_error() << "Can't load motion strategy" << std::endl;
			return false;
		}

		stream.read((char*)&m_motion_type, sizeof(m_motion_type));

		return true;
	}
}