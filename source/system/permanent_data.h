#ifndef _H_PUNK_SYSTEM_PERMANENT_DATA
#define _H_PUNK_SYSTEM_PERMANENT_DATA

#include "../config.h"
#include "storable_data.h"

namespace System
{
	class PUNK_ENGINE PermanentData : public StorableData
	{
		int m_type;
	public:
		int GetType() const { return m_type; }
		void SetType(int type) { m_type = type; }
	};
}

#endif	//	_H_PUNK_SYSTEM_PERMANENT_DATA