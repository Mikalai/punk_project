#ifndef _H_PUNK_UTILITY_DECL_PROPERTY
#define _H_PUNK_UTILITY_DECL_PROPERTY

#define PROPERTY(TYPE, NAME, PARAMETER) \
	TYPE& Get##NAME() { return PARAMETER; } \
	const TYPE& Get##NAME() const { return PARAMETER; }\
	void Set##NAME(const TYPE& value) { PARAMETER = value; }

#endif