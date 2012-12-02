#ifndef _H_PUNK_SYSTEM_TYPE
#define _H_PUNK_SYSTEM_TYPE

namespace System
{
	class Type
	{
	public:
		void f()
		{
			typeid(*this).name();
		}
	};
}

#endif	//	_H_PUNK_SYSTEM_TYPE