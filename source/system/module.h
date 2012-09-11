#ifndef _H_PUNK_LOGIC_MODULE
#define _H_PUNK_LOGIC_MODULE

namespace System
{
	class Module
	{
	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual ~Module() {};
	};
};

#endif