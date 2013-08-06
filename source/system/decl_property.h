#ifndef _H_PUNK_SYSTEM_DECL_PROPERTY
#define _H_PUNK_SYSTEM_DECL_PROPERTY

#define PROPERTY(TYPE, NAME, FIELD) inline void Set##NAME(const TYPE& value) { FIELD = value; } \
	inline const TYPE& Get##NAME() const { return FIELD; } \
	inline TYPE& Get##NAME() { return FIELD; }

#endif	//	_H_PUNK_SYSTEM_DECL_PROPERTY