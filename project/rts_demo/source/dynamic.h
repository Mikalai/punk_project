#ifndef _H_RTS_DEMO_DYNAMIC
#define _H_RTS_DEMO_DYNAMIC

class IDynamic
{
public:
	virtual void Update(double time, double dt) = 0;
	virtual bool NeedRemove() = 0;
	virtual bool NeedDelete() = 0;
	virtual ~IDynamic() {}
};

#endif	//	_H_RTS_DEMO_DYNAMIC